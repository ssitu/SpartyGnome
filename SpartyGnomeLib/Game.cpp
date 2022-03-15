/**
 * @file Game.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Item.h"
#include "BackgroundImage.h"
#include "Wall.h"
#include "PlatformF.h"
#include "ItemDoor.h"
#include "ItemMoney.h"
#include "Villain.h"
#include "ItemTuitionUp.h"
#include "Game.h"
#include "DrawStaticVisitor.h"
#include "DrawScrollingVisitor.h"
#include "VerticalCollisionVisitor.h"
#include "ItemMessage.h"
#include "DrawMessagesVisitor.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

const wstring LevelsDir = L"levels/";
const wstring LevelPrefix = L"level";

const int DefaultLevel = 1;
const double FreezeTime = 2;

Game::Game()
{
    Game::Clear();
    //Add SpartyGnome
    mGnome = make_shared<ItemSpartyGnome>(this);
}

/**
 * Passes the given visitor to all items for them to accept
 * @param visitor The visitor to accept
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Draw the game area
 * @param graphics The wxWidgets graphics context on which to draw
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Automatic Scaling
    //
    mScale = double(height)/double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double) width/mScale;
    graphics->PushState();

    //
    // Draw in virtual pixels on the graphics context
    //

    // Draw static items
    DrawStaticVisitor staticDrawer(graphics);
    Game::Accept(&staticDrawer);

    // There must be a gnome, but avoid crash if there isn't
    if (mGnome != nullptr)
    {
        auto xOffset = (double) -mGnome->GetX()+virtualWidth/2.0f;
        graphics->Translate(xOffset, 0);
    }

    // Draw scrolling items
    DrawScrollingVisitor scrollingDrawer(graphics);
    Game::Accept(&scrollingDrawer);

    // Draw Gnome last, so that it stays on top of other items
    mGnome->Draw(graphics);

    //Will need messages to stay on top of everything
    DrawMessagesVisitor messagesVisitor(graphics);
    Game::Accept(&messagesVisitor);

    graphics->PopState();
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i!=mItems.rend(); i++) {
        if ((*i)->HitTest(x, y)) {
            return *i;
        }
    }

    return nullptr;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    if (mFreeze > 0)
    {
        //Not concerned about a negative freeze time
        mFreeze -= elapsed;
    }
    else
    {
        for (auto item: mItems)
        {
            item->Update(elapsed);
        }
    }
}

/**
 * Add a Gnome to the game
 * @param gnome Gnome to add
 */
void Game::AddGnome(std::shared_ptr<ItemSpartyGnome> gnome)
{
    mItems.push_back(gnome);
    mGnome = gnome;
}

/**
 * Add an item to the game
 * @param item
 */
void Game::Add(shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add an item to the game
 * @param item New item to add
 * @param x x location of item
 * @param y y location of item
 */
void Game::Add(std::shared_ptr<Item> item, double x, double y)
{
    item->SetLocation(x, y);
    mItems.push_back(item);
}

/**
 * Make a item appear on top of the rest of the items.
 * @param mGrabbedItem shared pointer to an item, item to be appeared on top of other items.
*/
void Game::NewOrder(std::shared_ptr<Item> mGrabbedItem)
{
    auto loc = find(begin(mItems), end(mItems), mGrabbedItem);
    if (loc!=end(mItems)) {
        mItems.erase(loc);
    }
    mItems.push_back(mGrabbedItem);
}

/**
 * Clears the list of items, except for the Gnome
 */
void Game::Clear()
{
    mItems.clear();
    mItems.push_back(mGnome);
}

/**
 * Load a level number
 *
 * @param int The level number
 */
void Game::LevelLoad(const wstring& filename)
{
    wxXmlDocument xml;
    if (!xml.Load(filename)) {
        wxMessageBox(L"Error loading XML: cannot load XML file\nfile: "+filename);
        return;
    }

    this->Clear();

    // Get the root node, should be level
    auto root = xml.GetRoot();
    wxASSERT(root->GetName()==L"level");
    // <level width="1024" height="1024" start-y="572" start-x="468">
    long width;
    root->GetAttribute(L"width", L"100").ToLong(&width);
    long height;
    root->GetAttribute(L"height", L"100").ToLong(&height);
    root->GetAttribute(L"start-y", L"100").ToLong(&mStartY);
    root->GetAttribute(L"start-x", L"100").ToLong(&mStartX);

    // Get item declarations
    auto declarations = root->GetChildren();
    wxASSERT(declarations->GetName()==L"declarations");

    // Need a way to store the id with its respective information for that item type
    // Using hashtable to map ids to its respective XML node
    std::unordered_map<wxString, wxXmlNode*> declarations_table;
    // Iterate over declarations
    for (auto decl = declarations->GetChildren(); decl; decl = decl->GetNext()) {
        // Store info
        // item type
        auto type = decl->GetName(); // Can be used to test for correct format of the XML, unused for now

        // iterate over attributes and add them to the table
        // first attribute is id of declarations
        wstring id = decl->GetAttribute(L"id").ToStdWstring();
        // Map id to list
        declarations_table[id] = decl;
    }

    // Get item list
    auto items = declarations->GetNext();
    wxASSERT(items->GetName()==L"items");

    // Iterate over items
    for (auto item = items->GetChildren(); item; item = item->GetNext()) {
        LoadXmlItem(declarations_table, item);
    }

    // Use the loaded start location
    mGnome->DisableGravity();
    mGnome->SetLocation(mStartX, mStartY);
}

/**
 * Loads an item into the game, given a table for the item declarations and the XML node with item info
 *
 * @param declarations_table The table, mapping ids to declarations
 * @param item The particular item to load
 */
void Game::LoadXmlItem(const std::unordered_map<wxString,
                                                wxXmlNode*>& declarations_table, const wxXmlNode* item)
{
    auto type = item->GetName(); // Type of item
    //Get the id for the item declaration
    auto id = item->GetAttribute(L"id");
    //Get the declaration for the item id
    auto declaration = declarations_table.at(id);
    std::shared_ptr<Item> loadedItem = nullptr;
    //Choose which Item to make based on the type given
    if (type==L"background")
    {
        loadedItem = make_shared<BackgroundImage>(declaration, item);
    }
    else if (type==L"platform")
    {
        loadedItem = make_shared<Platform>(declaration, item);
    }
    else if (type==L"platformf") {
        loadedItem = make_shared<PlatformF>(declaration, item);
    }
    else if (type==L"wall")
    {
        loadedItem = make_shared<Wall>(declaration, item);
    }
    else if (type==L"door")
    {
        loadedItem = make_shared<ItemDoor>(declaration, item);
    }
    else if (type==L"money")
    {
        loadedItem = make_shared<ItemMoney>(declaration, item);
    }
    else if (type==L"villain")
    {
        loadedItem = make_shared<Villain>(declaration, item);
    }
    else if (type==L"tuition-up")
    {
        loadedItem = make_shared<ItemTuitionUp>(declaration, item);
    }
    else
    {
        wxMessageBox(L"Error loading XML: Item of type \"" + type + L"\" is not implemented or does not exist.");
    }
    if (loadedItem != nullptr) {
        Add(loadedItem);
    }
}

/**
 * Save the game as a .game XML file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the game to
 */
void Game::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"level");
    xmlDoc.SetRoot(root);
    root->AddAttribute(L"width", L"1024");
    root->AddAttribute(L"height", L"1024");
    root->AddAttribute(L"start-y", to_wstring(mStartY));
    root->AddAttribute(L"start-x", to_wstring(mStartX));

    auto declarations = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
    auto items = new wxXmlNode(wxXML_ELEMENT_NODE, L"items");

    // Iterate over all items and save them
    for (auto item: mItems) {
        if (item->GetId() != L"i000")
        {
            item->XmlSave(items, declarations);
        }
    }

    root->SetChildren(declarations);

    declarations->SetNext(items);

    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION)) {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

/**
 * Returns the item that the given item is vertically collided with, nullptr otherwise
 * @param item The item to determine collisions with
 * @return The item that is colliding with the given item, nullptr otherwise
 */
shared_ptr<Item> Game::VerticalCollisionTest(Item* item)
{
    VerticalCollisionVisitor visitor(item);
    for (auto oItem : mItems)
    {
        oItem->Accept(&visitor);
        if (visitor.IsColliding())
        {
            return oItem;
        }
    }
    return nullptr;
}

/**
 * Loads the default level
 */
void Game::LevelLoadDefault()
{
    LevelLoad(DefaultLevel);
}

/**
 * Loads the level number
 * @param levelNum
 */
void Game::LevelLoad(int levelNum)
{
    wstring filename = LevelsDir + LevelPrefix + to_wstring(levelNum) + L".xml";
    Game::LevelLoad(filename);

    // Freeze the game
    Game::Freeze(FreezeTime);

    // Display the start message
    Game::DisplayStartMessage(levelNum);
}

/**
 * Freezes the game for the given amount of time in seconds
 * @param seconds Number of seconds to freeze the game for
 */
void Game::Freeze(double seconds)
{
    mFreeze = seconds;
}

/**
 * Display the starting message for a level number
 * @param levelNum The level number
 */
void Game::DisplayStartMessage(int levelNum)
{
    wstring message = L"Level " + to_wstring(levelNum) + L" Begin!";
    auto messageItem = make_shared<ItemMessage>(this, message, FreezeTime);
    auto centerX = mGnome->GetX();
    auto centerY = Height / 2;
    Game::Add(messageItem, centerX, centerY);
}

/**
 * Removes an item from the game
 * @param item The item to remove
 */
void Game::RemoveItem(Item* item)
{
    auto pos = std::remove_if(mItems.begin(), mItems.end(),
            [item](shared_ptr<Item> x){return x.get() == item;});
    mItems.erase(pos);
}

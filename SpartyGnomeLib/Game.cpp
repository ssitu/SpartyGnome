/**
 * @file Game.cpp
 * @author Gabriel Misajlovski, Simon Situ, ryanl, ashrey, Connor
 */

#include "pch.h"

#include <wx/graphics.h>
#include <string>

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
#include "SolidCollisionVisitor.h"
#include "InteractionCollisionVisitor.h"
#include "ItemMessage.h"
#include "DrawMessagesVisitor.h"
#include "ItemLevelTimer.h"
#include "ItemScoreBoard.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;
/// Image Directory
const wstring ImageDir = L"images/";
/// Levels Directory
const wstring LevelsDir = L"levels/";
/// LevelPrefix Directory
const wstring LevelPrefix = L"level";
/// Default Level to start
const int DefaultLevel = 1;
/// Time for freeze
const double FreezeTime = 2;

Game::Game()
{
    //Add SpartyGnome
    mGnome = make_shared<ItemSpartyGnome>(this);
    //Add to the list
    mItems.push_back(mGnome);
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


//    // Draw static items
//    DrawStaticVisitor staticDrawer(graphics);
//    Game::Accept(&staticDrawer);

    double xOffset = 0;
    // There must be a gnome, but avoid crash if there isn't
    if (mGnome != nullptr)
    {
        xOffset = (double) -mGnome->GetX()+virtualWidth/2.0f;
    }
    graphics->Translate(xOffset, 0);

    // Draw scrolling items
    DrawScrollingVisitor scrollingDrawer(graphics);
    Game::Accept(&scrollingDrawer);


    // Draw Gnome last, so that it stays on top of other items
    mGnome->Draw(graphics);

    // Will need messages to stay on top of everything
    DrawMessagesVisitor messagesVisitor(graphics);
    Game::Accept(&messagesVisitor);
    graphics->PopState();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    if (mFreezeLoseWin > 0)
    {
        mFreezeLoseWin -= elapsed;
    }
    else
    {
        if (mLost == true || mWin == true)
        {
            Game::LevelLoad(mLevelNum);
            mLost = false;
            mWin = false;
        }
        if (mFreeze>0) {
            //Not concerned about a negative freeze time
            mFreeze -= elapsed;
        }
        else {
            //Make a copy of the items to iterate over
            std::vector<std::shared_ptr<Item>> items;
            for (auto item: mItems) {
                items.push_back(item);
            }
            //Iterate over the copy so that if mItems were to be modified, the loop is still valid
            for (auto item: items) {
                item->Update(elapsed);
            }
        }
    }
}

/**
 * Add an item to the game
 * @param item item to add to the game
 */
void Game::Add(std::shared_ptr<Item> item)
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
 * Clears the list of items, then adds the Gnome back
 */
void Game::Clear()
{
    mItems.clear();
    mItems.push_back(mGnome);
}

/**
 * Load a level
 * @param filename The xml filename for the level
 */
void Game::LevelLoad(const std::wstring& filename)
{
    wxXmlDocument xml;
    if (!xml.Load(filename))
    {
        wxMessageBox(L"Error loading XML: cannot load XML file\nfile: "+filename);
        return;
    }

    Reset();

    // Get the root node, should be level
    auto root = xml.GetRoot();
    // <level width="1024" height="1024" start-y="572" start-x="468">
    long width;
    root->GetAttribute(L"width", L"0").ToLong(&width);
    long height;
    root->GetAttribute(L"height", L"0").ToLong(&height);
    root->GetAttribute(L"start-y", L"0").ToLong(&mStartY);
    root->GetAttribute(L"start-x", L"0").ToLong(&mStartX);

    // Get item declarations
    auto declarations = root->GetChildren();

    // Need a way to store the id with its respective information for that item type
    // Using hashtable to map ids to its respective XML node
    std::unordered_map<wxString, wxXmlNode*> declarations_table;
    // Iterate over declarations
    for (auto decl = declarations->GetChildren(); decl; decl = decl->GetNext())
    {
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

    // Iterate over items
    for (auto item = items->GetChildren(); item; item = item->GetNext()) {
        LoadXmlItem(declarations_table, item);
    }

    // Use the loaded start location
    mGnome->DisableGravity();
    mGnome->SetLocation(mStartX, mStartY);

    Setup();
}

/**
 * Loads an item into the game, given a table for the item declarations and the XML node with item info
 *
 * @param declarations_table The table, mapping ids to declarations
 * @param item The particular item to load
 */
void Game::LoadXmlItem(const std::unordered_map<wxString, wxXmlNode*>& declarations_table, const wxXmlNode* item)
{
    // Type of item based on Node Name
    auto type = item->GetName();

    //Get the id for the item declaration
    auto id = item->GetAttribute(L"id");

    //Get the declaration for the item id
    auto declaration = declarations_table.at(id);

    // Set default loadedItem to nullptr
    std::shared_ptr<Item> loadedItem = nullptr;

    // Choose which Item pointer to make based on the type given
    if (type==L"background")
    {
        loadedItem = make_shared<BackgroundImage>(declaration, item, this);
    }
    else if (type==L"platform")
    {
        loadedItem = make_shared<Platform>(declaration, item, this);
    }
    else if (type==L"platformf")
    {
        loadedItem = make_shared<PlatformF>(declaration, item, this);
    }
    else if (type==L"wall")
    {
        loadedItem = make_shared<Wall>(declaration, item, this);
    }
    else if (type==L"door")
    {
        loadedItem = make_shared<ItemDoor>(declaration, item, this);
        loadedItem->SetGame(this);
    }
    else if (type==L"money")
    {
        loadedItem = make_shared<ItemMoney>(declaration, item, this);
    }
    else if (type==L"villain")
    {
        loadedItem = make_shared<Villain>(declaration, item, this);
    }
    else if (type==L"tuition-up")
    {
        loadedItem = make_shared<ItemTuitionUp>(declaration, item, this);
    }
    else
    {
        // Error handler if Item type is not implemented into the program
        wxMessageBox(L"Error loading XML: Item of type \"" + type + L"\" is not implemented or does not exist.");
    }

    // If loadedItem exists...
    if (loadedItem != nullptr) {
        // Add it to the game
        Add(loadedItem);
    }
    // else end this function
}

/**
 * Save the game as a game .xml file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the game to
 */
void Game::Save(const wxString& filename)
{
    // Create a new xml
    wxXmlDocument xmlDoc;

    // create the root node
    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"level");
    xmlDoc.SetRoot(root);

    // Add attributes for the root node
    root->AddAttribute(L"width", L"1024");
    root->AddAttribute(L"height", L"1024");
    root->AddAttribute(L"start-y", to_wstring(mStartY));
    root->AddAttribute(L"start-x", to_wstring(mStartX));

    // Create the root's 2 child nodes, items and declarations
    auto declarations = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
    auto items = new wxXmlNode(wxXML_ELEMENT_NODE, L"items");

    // Iterate over all items and save them
    for (auto item: mItems)
    {
        // if the Item ID is NOT the gnome...
        if (item->GetId() != L"i000")
        {
            // add it to the xml files
            item->XmlSave(items, declarations);
        }
    }

    // Set declarations and items as the root's children
    root->SetChildren(declarations);
    declarations->SetNext(items);

    // Error handler if save fails
    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION)) {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

/**
 * Returns the solid item that the given item has collided with, nullptr otherwise
 * @param item The item to determine collisions with
 * @return The item that is considered to be solid that is colliding with the given item, nullptr otherwise
 */
shared_ptr<Item> Game::SolidCollisionTest(Item* item)
{
    // Create a visitor to test collisions.
    SolidCollisionVisitor visitor(item);

    auto itemsSafe(mItems);

    // Iterate over the items in the game
    for (auto oItem : itemsSafe)
    {
        // Accept the visitor into each item
        oItem->Accept(&visitor);

        // if the item being visited is colliding with the parameter item...
        if (visitor.IsColliding())
        {
            // return the colliding item
            return oItem;
        }
    }

    // if no items are colliding, return nullptr
    return nullptr;
}

/**
 * The collision test for interactable items
 * @param item The item to test collisions with
 */
void Game::InteractableCollisionTest(Item* item)
{
    InteractionCollisionVisitor visitor(item);
    auto itemsSafe(mItems);
    for (auto oItem: itemsSafe)
    {
        if(oItem.get()!= item) {
            oItem->Accept(&visitor);
            if (visitor.IsColliding()) {
                oItem->OnCollision(item);
            }
        }
    }
}

/**
 * Loads the default level
 */
void Game::LevelLoadDefault()
{
    LevelLoad(DefaultLevel);
}

/**
 * Loads the level with a given number
 * @param levelNum number of the level to load
 */
void Game::LevelLoad(int levelNum)
{
    // Clear the game
    Game::Clear();
    // Store the level number for reloading level upon death
    // mLevelNum = levelNum;

    // mLevelNum = levelNum;
    // setting the level number
    Game::SetLevelNum(levelNum);
    // create directory to load
    wstring filename = LevelsDir + LevelPrefix + to_wstring(levelNum) + L".xml";

    // Load the level
    Game::LevelLoad(filename);

    // Display the start message
    Game::DisplayStartMessage(levelNum);
}

/**
 * Display the starting message for a level number
 * @param levelNum The level number
 */
void Game::DisplayStartMessage(int levelNum)
{
    mGnome->AnimateStop();
    wstring message = L"Level " + to_wstring(levelNum) + L" Begin!";
    Game::FreezeScreenMessage(message);
}

/**
 * Removes an item from the game
 * @param item The item to remove
 */
void Game::RemoveItem(Item* item)
{
    // Get an iterator at the position of the item in mItems
    auto pos = std::remove_if(mItems.begin(), mItems.end(),
            [item](shared_ptr<Item> x){return x.get() == item;});

    // erase the item
    mItems.erase(pos);
}

/**
 * Display the losing message
 */
void Game::DisplayLoseMessage()
{
    wstring message = L"You Lose!";
    Game::FreezeScreenMessage(message);

    Game::FreezeLoseWin(FreezeTime);
    mLost = true;
}

/**
 * Display the win message
 */
void Game::DisplayWinMessage()
{
    wstring message = L"Level Complete!";
    Game::FreezeScreenMessage(message);

    Game::FreezeLoseWin(FreezeTime);
    mWin = true;
}

/**
 * Display a screen message and freeze the screen
 * @param message Message to show
 */
void Game::FreezeScreenMessage(const wstring& message)
{
    auto messageItem = make_shared<ItemMessage>(this, message, 0);
    auto centerX = mGnome->GetX();
    auto centerY = Height / 2;
    Game::Add(messageItem, centerX, centerY);
    Game::Freeze(FreezeTime);
}

/**
 * Returns the bitmap of the specified image file
 * @param filename the name of the image file
 * @return the bitmap of the specified image file
 */
std::shared_ptr<wxBitmap> Game::GetBitmap(const std::wstring &filename){
    // If the bitmap for the specific file is not in mBitmaps...
    if(mBitmaps.count(filename) == 0)
    {
        // Add the bitmap to mBitmaps
        auto imagePath = ImageDir + filename;
        wxImage image(imagePath, wxBITMAP_TYPE_ANY);
        mBitmaps[filename] = make_shared<wxBitmap>(image);
    }

    // Return the corresponding bitmap for this image file
    return mBitmaps.at(filename);
}

/**
 * Resets the game to initial conditions
 */
void Game::Reset()
{
    Clear();
    mGnome->DisableGravity();
}

/**
 * Setup the game, assuming level is loaded
 */
 void Game::Setup()
{
     // Create the level timer
     auto timer = make_shared<ItemLevelTimer>(this);
     Add(timer);
     mBoard = make_shared<ItemScoreBoard>(this);
     Add(mBoard);
     mGnome->EnableGravity();
}

/**
 * Get the world x position of the given center offset
 * @param x The x offset from the center of the screen to convert
 * @return The world x coordinate
 */
int Game::GetScreenToWorldX(int x)
{
    auto actualX = x / mScale;
    return GetGnome()->GetX() + actualX;
}

/**
 * Add to the score count
 * @param change The amount to add
 */
void Game::IncrementScore(int change)
{
    mBoard->IncrementScore(change);
}

/**
 * Obtain the height of the game area in unscaled pixels
 * @return The game area in unscaled pixels
 */
int Game::GetGameAreaHeight()
{
    return Height;
}



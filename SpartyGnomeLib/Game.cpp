/**
 * @file Game.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Item.h"
#include "BackgroundImage.h"
#include "Wall.h"
#include "Game.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

const wstring LevelsDir = L"levels/";
const wstring DefaultLevel = LevelsDir+L"level0.xml";

const bool ErrorMessages = false;

Game::Game()
{
    //Add SpartyGnome
    mGnome = make_shared<ItemSpartyGnome>(this);
    mItems.push_back(mGnome);
    //Load the default level
    LevelLoad(DefaultLevel);
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


    // There must be a gnome in a level, but avoid crash if there isn't
    if (mGnome!=nullptr) {
        auto xOffset = (double) -mGnome->GetX()+virtualWidth/2.0f;
        graphics->Translate(xOffset, 0);
    }

    // Draw scrolling items
    // Drawing every item for now
    for (const auto& item: mItems) {
        item->Draw(graphics);
    }
    // Draw Gnome last, so that it stays on top of other items
    mGnome->Draw(graphics);
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
    for (auto item: mItems) {
        item->Update(elapsed);
    }
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::AddGnome(std::shared_ptr<ItemSpartyGnome> item)
{
    mItems.push_back(item);
    mGnome = item;
}

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
 * Load a level from an xml file
 *
 * @param filename The wxString of the file path
 */
void Game::LevelLoad(const wxString& filename)
{
    wxXmlDocument xml;
    if (!xml.Load(filename)) {
        if (ErrorMessages) {
            wxMessageBox(L"Error loading XML: cannot load XML file\nfile: "+filename);
        }
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
    long startY;
    root->GetAttribute(L"start-y", L"100").ToLong(&startY);
    long startX;
    root->GetAttribute(L"start-x", L"100").ToLong(&startX);

    // Use the loaded start location
    mGnome->SetLocation(startX, startY);

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
    if (type==L"background") {
        loadedItem = make_shared<BackgroundImage>(declaration, item);
    }
    else if (type==L"platform") {
        loadedItem = make_shared<Platform>(declaration, item);
    }
    else if (type==L"wall") {
        loadedItem = make_shared<Wall>(declaration, item);
    }
    else {
        if (ErrorMessages) {
            wxMessageBox(L"Error loading XML: Item of type \""+type+L"\" is not implemented");
        }
    }
    if (loadedItem!=nullptr) {
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

    auto declarations = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
    auto items = new wxXmlNode(wxXML_ELEMENT_NODE, L"items");

    root->SetChildren(declarations);
    root->SetChildren(items);

    // Iterate over all items and save them
    for (auto item: mItems) {
        item->XmlSave(items);
    }

    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION)) {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

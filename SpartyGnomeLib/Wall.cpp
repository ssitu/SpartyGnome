/**
 * @file Wall.cpp
 * @authors cro56, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>
#include <wx/graphics.h>

#include "Wall.h"

using namespace std;

/// Default wall image filepath
const wstring imageWallName = L"images/wall1.png";

/// Wall tile size
const int TileSize = 32;

/**
 * Constructor
 * @param game Game this item is a member of
 */
Wall::Wall(Game* game) : Item(game, imageWallName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration node we are pulling from
 * @param item The item node we are pulling from
 * @param game The Game this Item is apart of
 */
Wall::Wall(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return 1-2 nodes that were added to the save
 */
pair<wxXmlNode*, wxXmlNode*> Wall::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    // Pull nodes from Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Change itemNode to type wall
    itemNode->SetName(L"wall");

    // if the declarationNode does not already exist
    if (declarationNode!=nullptr) {
        // Create a declaration node
        declarationNode->SetName(L"wall");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}

/**
 * Draws this wall to the given graphics context
 * @param gc The graphics context we are drawing on
 */
void Wall::Draw(shared_ptr<wxGraphicsContext> gc)
{
    int startX = Item::GetX() - Item::GetWidth() / 2;
    int startY = Item::GetY() - Item::GetHeight() / 2;
    //Draw segments until the height is filled
    for (int i = 0; i < Item::GetHeight(); i += TileSize)
    {
        gc->DrawBitmap(*GetBitmap(),
                startX,
                startY+i,
                Item::GetWidth()+1,
                TileSize+1);
    }
}



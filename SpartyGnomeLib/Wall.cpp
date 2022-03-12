/**
 * @file Wall.cpp
 * @authors cro56, Gabriel Misajlovski
 */
#include "pch.h"

#include <string>
#include <wx/graphics.h>

#include "Wall.h"

using namespace std;

const wstring imageWallName = L"images/wall1.png";
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
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 */
Wall::Wall(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
pair<wxXmlNode*, wxXmlNode*> Wall::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto itemNode = Item::XmlSave(node1, node2).first;
    auto declarationNode = Item::XmlSave(node1, node2).second;
    itemNode->SetName(L"wall");
    declarationNode->SetName(L"wall");

    return make_pair(itemNode, declarationNode);
}

/**
 * Draws this wall to the given graphics context
 * @param gc The graphics context
 */
void Wall::Draw(std::shared_ptr<wxGraphicsContext> gc)
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



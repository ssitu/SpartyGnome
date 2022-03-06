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
wxXmlNode* Wall::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"wall");

    return itemNode;
}

/**
 * Draws this wall to the given graphics context
 * @param gc The graphics context
 */
void Wall::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    gc->DrawBitmap(*GetBitmap(),
                int(GetX()-GetWidth()/2),
                int(GetY()-GetHeight()/2),
                GetWidth()+1,
                GetHeight()+2);
}



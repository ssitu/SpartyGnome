/**
 * @file Wall.cpp
 * @authors cro56, Gabriel Misajlovski
 */
#include "pch.h"

#include <string>

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



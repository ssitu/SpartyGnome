/**
 * @file Platform.cpp
 * @author ryanl, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "Platform.h"

using namespace std;

const wstring PlatformName = L"images/snow.png";

class Game;

/**
 * Constructor
 * @param game Game this item is a member of
 */
Platform::Platform(Game *game) : Item(game, PlatformName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 */
Platform::Platform(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this platform to an XML node
 * @param node The parent node we are going to be a child of
 * @return The node we are doing to add to the parent.
 */
wxXmlNode* Platform::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"platform");
    return itemNode;
}


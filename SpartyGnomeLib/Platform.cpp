/**
 * @file Platform.cpp
 * @author ryanl
 */

#include "pch.h"
#include "Platform.h"
#include <string>
using namespace std;
const wstring PlatformName = L"images/snow.png";
const wstring left_image = L"images/snow-left.png";
const wstring mid_image = L"images/snow-mid.png";
const wstring right_image = L"images/snow-right.png";

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
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Platform::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"platform");

    return itemNode;
}


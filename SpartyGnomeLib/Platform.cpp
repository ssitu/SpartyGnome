/**
 * @file Platform.cpp
 * @author ryanl
 */

#include "pch.h"
#include "Platform.h"
#include <string>
using namespace std;
const wstring PlatformName = L"images/snow.png";

/**
 * Constructor
 * @param game Game this item is a member of
 */
Platform::Platform(Game *game) : Item(game, PlatformName)
{
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Platform::XmlSave(wxXmlNode* node)
{
    auto itemNode = Platform::XmlSave(node);
    itemNode->AddAttribute(L"type", L"platform");

    return itemNode;
}


/**
 * @file Wall.cpp
 * @author cro56
 */
#include "pch.h"
#include "Wall.h"

Wall::Wall(Game* game, const std::wstring& imagePath) : Item(game, imagePath)
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
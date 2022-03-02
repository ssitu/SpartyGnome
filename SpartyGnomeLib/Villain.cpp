/**
 * @file Villain.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "Villain.h"

/**
 * Villain Constructor
 * @param game The game holding this item
 * @param imagePath The path to the image for this item
 */
Villain::Villain(Game* game, const std::wstring& imagePath) : Item(game, imagePath)
{

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Villain::XmlSave(wxXmlNode* node)
{
    auto itemNode = Villain::XmlSave(node);
    itemNode->AddAttribute(L"type", L"villain");

    return itemNode;
}

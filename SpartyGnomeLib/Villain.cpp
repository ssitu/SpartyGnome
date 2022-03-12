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
std::pair<wxXmlNode*, wxXmlNode*> Villain::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"villain");

    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"villain");
        return std::make_pair(itemNode, declarationNode);
    }

    return std::make_pair(itemNode, nullptr);
}

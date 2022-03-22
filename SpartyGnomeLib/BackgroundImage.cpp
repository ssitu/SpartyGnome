/**
 * @file BackgroundImage.cpp
 * 
 * @author Simon Situ, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "BackgroundImage.h"

using namespace std;
const wstring BackGroundImageName = L"backgroundForest.png";

/**
 * Initialize the background image into the game
 * @param game The game this background is a part of
 */
BackgroundImage::BackgroundImage(Game* game) : Item(game, BackGroundImageName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 * @param game The Game that this Item is apart of
 */
BackgroundImage::BackgroundImage(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{

}

/**
 * Save this item to an XML node
 * @param node1 The parent Item node we are going to be a child of
 * @param node2 The declaration Item node we are going to be a child of
 * @return pair<wxXmlNode*, wxXmlNode*> the nodes we are adding to the parents
 */
std::pair<wxXmlNode*, wxXmlNode*> BackgroundImage::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");
    itemNode->SetName(L"background");

    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"background");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}
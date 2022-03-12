/**
 * @file BackgroundImage.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"

#include <string>

#include "BackgroundImage.h"

using namespace std;
const wstring BackGroundImageName = L"images/backgroundForest.png";

BackgroundImage::BackgroundImage(Game* game) : Item(game, BackGroundImageName)
{

}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 */
BackgroundImage::BackgroundImage(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
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
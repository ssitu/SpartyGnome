/**
 * @file ItemTuitionUp.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemTuitionUp.h"

using namespace std;

const wstring TuitionUpImageName = L"images/stanley.png";

ItemTuitionUp::ItemTuitionUp(Game* game) : Item(game, TuitionUpImageName)
{

}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item
 */
ItemTuitionUp::ItemTuitionUp(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this item to an XML node
 * @param node1 The first parent node we are going to be a child of
 * @param node2 The second parent node we are going to be a child of
 * @return either single itemNode or pair with an itemNode and declarationNode
 */
pair<wxXmlNode*, wxXmlNode*> ItemTuitionUp::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"tuition-up");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");
    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"tuition-up");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}
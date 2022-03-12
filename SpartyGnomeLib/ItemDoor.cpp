/**
 * @file ItemDoor.cpp
 * @author ashrey, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemDoor.h"

using namespace std;

const wstring DoorImageName = L"images/door.png";

ItemDoor::ItemDoor(Game* game) : Item(game, DoorImageName)
{

}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item
 */
ItemDoor::ItemDoor(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this item to an XML node
 * @param node1 The first parent node we are going to be a child of
 * @param node2 The second parent node we are going to be a child of
 * @return either single itemNode or pair with an itemNode and declarationNode
 */
pair<wxXmlNode*, wxXmlNode*> ItemDoor::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"door");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");
    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"door");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}
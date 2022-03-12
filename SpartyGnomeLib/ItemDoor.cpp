/**
 * @file ItemDoor.cpp
 * @author ashrey
 */

#include "pch.h"
#include<string>
using namespace std;
#include "ItemDoor.h"
const wstring DoorImageName = L"images/door.png";

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
std::pair<wxXmlNode*, wxXmlNode*> ItemDoor::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"door");
    declarationNode->SetName(L"door");

    return make_pair(itemNode, declarationNode);
}
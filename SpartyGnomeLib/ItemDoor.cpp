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
wxXmlNode* ItemDoor::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->SetName(L"door");

    return itemNode;
}
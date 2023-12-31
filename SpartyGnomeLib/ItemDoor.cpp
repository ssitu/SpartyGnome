/**
 * @file ItemDoor.cpp
 * @author ashrey, Gabriel Misajlovski, ryanl
 */

#include "pch.h"

#include <string>

#include "ItemDoor.h"

using namespace std;

/// Collision distance for the door in pixels
const double CollisionDistance = 20;

/// A default door image
const wstring DoorImageName = L"door.png";

/// The bottom of the level range
const int LevelRangeBottom = 1;

/// THe top of the level range
const int LevelRangeTop = 3;

/**
 * The base constructor for this item
 * @param game The game this item is apart of
 */
ItemDoor::ItemDoor(Game* game) : Item(game, DoorImageName)
{

}

/**
 * The constructor used to load from XML
 * @param declaration The declaration xml node
 * @param item The item xml node
 * @param game The Game that this Item is apart of
 */
ItemDoor::ItemDoor(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{

}

/**
 * Save this item to an XML node
 * @param node1 The items parent node we are going to be a child of
 * @param node2 The declarations parent node we are going to be a child of
 * @return either single itemNode or pair with an itemNode and declarationNode
 */
pair<wxXmlNode*, wxXmlNode*> ItemDoor::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    // Create new nodes based on Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Add door-specific attributes and delete attributes unnecessary for door
    itemNode->SetName(L"door");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");

    // Add declaration node if not already exists
    if (declarationNode!=nullptr)
    {
        declarationNode->SetName(L"door");

        // return pair of itemNode and declarationNode
        return make_pair(itemNode, declarationNode);
    }

    // return itemNode
    return make_pair(itemNode, nullptr);
}

/**
 * The collision test function for this door
 * @param item The item to test collisions with
 * @return true if the test found a collision, false otherwise
 */
bool ItemDoor::CollisionTest(Item* item)
{
    // Collision for door is different from other items
    double dx = item->GetX() - GetX();
    double dy = item->GetY() - GetY();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance < CollisionDistance)
    {
        return true;
    }

    return false;
}

/**
 * The collision handler for this item
 * @param item The item that collided with this item
 */
void ItemDoor::OnCollision(Item* item)
{
    auto levelNum = GetGame()->GetLevelNum();
    if (LevelRangeBottom <= levelNum && levelNum < LevelRangeTop)
    {
        GetGame()->SetLevelNum(levelNum + 1);
    }
    else
    {
        GetGame()->SetLevelNum(LevelRangeTop);
    }
    GetGame()->DisplayWinMessage();
}
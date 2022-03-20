/**
 * @file ItemTuitionUp.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemTuitionUp.h"

using namespace std;

const wstring TuitionUpImageName = L"images/stanley.png";

const int RemoveHeight = 1174;

ItemTuitionUp::ItemTuitionUp(Game* game) : Item(game, TuitionUpImageName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration node of this item
 * @param item The item node of this item
 * @param game The Game that this item is apart of
 */
ItemTuitionUp::ItemTuitionUp(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{

}

/**
 * Save this item to an XML node
 * @param node1 The items parent node we are going to be a child of
 * @param node2 The declarations parent node we are going to be a child of
 * @return 1-2 nodes that were added to the XML File
 */
pair<wxXmlNode*, wxXmlNode*> ItemTuitionUp::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    // Get the item and declaration nodes from Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Edit itemNode attributes for this item
    itemNode->SetName(L"tuition-up");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");

    // If a declarationNode for this item does not already exist...
    if (declarationNode!=nullptr) {
        // Add the declarationNode
        declarationNode->SetName(L"tuition-up");

        // return both itemNode and declarationNode
        return make_pair(itemNode, declarationNode);
    }

    // return just the itemNode
    return make_pair(itemNode, nullptr);
}

void ItemTuitionUp::OnCollision(Item *item){
    //GetGame()->IncrementScore();
    mTuitionIncrease = true;
}

void ItemTuitionUp::Update(double elapsed){

    if (mTuitionIncrease){

        Item::Update(elapsed);
        SetLocation(GetX(),GetY()+mSpeedY*elapsed);


//        }
    }


}
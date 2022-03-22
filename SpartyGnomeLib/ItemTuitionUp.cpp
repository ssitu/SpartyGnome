/**
 * @file ItemTuitionUp.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemTuitionUp.h"
#include "MoneyValueVisitor.h"
using namespace std;

/// The default image
const wstring TuitionUpImageName = L"stanley.png";

/// The value to increase money by on pickup
const double ValueFactor = 0.1;

/// Pickup Message Specifications
const wstring MessageTuitionIncrease = L"Tuition Increase!";
///Duration for which the message is shown on pickup
const double Duration = 4;
///Width of text
int FontWidth = 25;
///height of the text
int FontHeight = 25;
///Velocity of the message
Vector MessageVelocity = Vector(0, -800);
///Acceleration of the message
Vector MessageAcceleration = Vector(0,-150);
///size change rate of the message
Vector MessageSizeChange = Vector(3,3);

/**
 * The base item constructor
 * @param game The Game that this item is apart of
 */
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
    if (declarationNode!=nullptr)
    {
        // Add the declarationNode
        declarationNode->SetName(L"tuition-up");

        // return both itemNode and declarationNode
        return make_pair(itemNode, declarationNode);
    }

    // return just the itemNode
    return make_pair(itemNode, nullptr);
}

/**
 * The collision handler for this item
 * @param item The item that collided with this item
 */
void ItemTuitionUp::OnCollision(Item *item)
{
    if(!mCollided)
    {
        mTuitionIncrease = true;
        mCollided = true;
        MoneyValueVisitor visitor(ValueFactor);
        GetGame()->Accept(&visitor);

        auto animatedMessage = std::make_shared<ItemMessageAnimated> (GetGame(), MessageTuitionIncrease, Duration,
                FontWidth, FontHeight, MessageVelocity, MessageAcceleration);
        animatedMessage->SetSizeChange(MessageSizeChange);
        GetGame()->Add(animatedMessage, GetX(),GetY());
    }
}

/**
 * The update function
 * @param elapsed The seconds elapses since the last update call
 */
void ItemTuitionUp::Update(double elapsed){
    if (mTuitionIncrease)
    {
        Item::Update(elapsed);
        SetLocation(GetX(),GetY() + mSpeedY * elapsed);
        auto removeHeight = GetGame()->GetGameAreaHeight() + GetHeight() / 2;
        if(GetY() > removeHeight)
        {
            GetGame()->RemoveItem(this);
        }
    }
}
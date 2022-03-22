/**
 * @file ItemMoney.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemMoney.h"


using namespace std;
///the default image
const wstring MoneyImageName = L"money100.png";
///Message for a $100 bill
const wstring Message100 = L"$100";
///message for a 1000$ bill
const wstring Message1000 = L"$1000";
///duration for which the message is displayed on collision
const double Duration = 4;
///width of message
const int FontWidth = 25;
///height of message
const int FontHeight = 25;
///velocity of message
Vector Velocity = Vector(0, -1000);

/**
 * Base constructor for this item
 * @param game Game that this item is apart of
 */
ItemMoney::ItemMoney(Game* game) : Item(game, MoneyImageName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 * @param game The Game that this item is apart of
 */
ItemMoney::ItemMoney(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{
    // get value of this money item
    declaration->GetAttribute(L"value", L"0").ToDouble(&mValue);
}

/**
 * Save this item to 1-2 XML nodes
 * @param node1 The items parent node we are going to be a child of
 * @param node2 The declarations parent node we are going to be a child of
 * @return 1-2 nodes that were added to the XML file
 */
pair<wxXmlNode*, wxXmlNode*> ItemMoney::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    // Get nodes from Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Set money-specific attributes and delete unnecessary attributes.
    itemNode->SetName(L"money");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");

    // Check to see if we need to add a child to declarations
    if (declarationNode!=nullptr)
    {
        declarationNode->SetName(L"money");

        // Value is added only to declarationNode
        declarationNode->AddAttribute(L"value", wxString::FromDouble(mValue));
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}

/**
 * On collision handler for this item
 * @param item The item that collided with this item
 */
void ItemMoney::OnCollision(Item *item)
{
    if(!mCollided)
    {
        mMoneyIncrease = true;
        GetGame()->IncrementScore(mValue);
        mCollided = true;
        if (mValue >= 100 && mValue < 1000)
        {
            std::shared_ptr<ItemMessageAnimated> animatedMessage = std::make_shared<ItemMessageAnimated> (GetGame(), Message100, Duration,
                    FontWidth, FontHeight, Velocity);
            GetGame()->Add(animatedMessage, GetX(),GetY());
        }
        else
        {
            std::shared_ptr<ItemMessageAnimated> animatedMessage = std::make_shared<ItemMessageAnimated>(GetGame(),
                    Message1000, Duration,FontWidth, FontHeight, Velocity);
            GetGame()->Add(animatedMessage, GetX(),GetY());
        }
    }
}

/**
 * The update handler for this item
 * @param elapsed The time elapsed since the last update call
 */
void ItemMoney::Update(double elapsed)
{
    if (mMoneyIncrease)
    {
        Item::Update(elapsed);
        SetLocation(GetX(),GetY()+mSpeedY*elapsed);
    }
}

/**
 * Setter for the value of this money item
 * @param moneyValue The new value to replace the current value
 */
void ItemMoney::SetValue(double moneyValue)
{
    mValue = moneyValue;
}



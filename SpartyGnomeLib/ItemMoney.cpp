/**
 * @file ItemMoney.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemMoney.h"


using namespace std;

const wstring MoneyImageName = L"images/money100.png";
const int scoreValue1 = 100;
const wstring message = L"$100";
const wstring message1 = L"$1000";
const double duration = 4;
const int fontWidth1 = 25;
const int fontHeight1 = 25;
Vector velocity1 = Vector(0, -1000);


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
    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"money");

        // Value is added only to declarationNode
        declarationNode->AddAttribute(L"value", wxString::FromDouble(mValue));
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}

void ItemMoney::OnCollision(Item *item){
    //GetGame()->IncrementScore();
    if(!mCollided){
        mMoneyIncrease = true;
        GetGame()->CallScoreBoard(mValue);
        mCollided = true;
//        GetGame()->Add(ItemMessageAnimated(GetGame(), )
        if (mValue >= 100 && mValue < 1000){
            std::shared_ptr<ItemMessageAnimated> animatedMessage = std::make_shared<ItemMessageAnimated> (GetGame(), message, duration,
                    fontWidth1, fontHeight1, velocity1);
            GetGame()->Add(animatedMessage, GetX(),GetY());
        }
        else {
            std::shared_ptr<ItemMessageAnimated> animatedMessage = std::make_shared<ItemMessageAnimated>(GetGame(),
                    message1, duration,fontWidth1, fontHeight1, velocity1);
            GetGame()->Add(animatedMessage, GetX(),GetY());
        }

    }


}

void ItemMoney::Update(double elapsed){

    if (mMoneyIncrease){

        Item::Update(elapsed);
        SetLocation(GetX(),GetY()+mSpeedY*elapsed);


//        }
    }


}

void ItemMoney::SetValue(double moneyValue){
    mValue = moneyValue;
}



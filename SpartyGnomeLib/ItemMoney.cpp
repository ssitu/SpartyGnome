/**
 * @file ItemMoney.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "ItemMoney.h"


using namespace std;

const wstring MoneyImageName = L"images/money100.png";

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





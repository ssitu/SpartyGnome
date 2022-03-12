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
 */
ItemMoney::ItemMoney(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
pair<wxXmlNode*, wxXmlNode*> ItemMoney::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"money");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");
    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"money");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}


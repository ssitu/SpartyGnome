/**
 * @file Villain.cpp
 * 
 * @author Simon Situ, Gabriel Misajlovski, ryanl
 */

#include "pch.h"

#include <string>

#include "Villain.h"

using namespace std;

const wstring villainImageName = L"images/UofM.png";

/**
 * Villain Constructor
 * @param game The game holding this item
 * @param imagePath The path to the image for this item
 */
Villain::Villain(Game* game) : Item(game, villainImageName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item
 */
Villain::Villain(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
std::pair<wxXmlNode*, wxXmlNode*> Villain::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;
    itemNode->SetName(L"villain");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");

    if (declarationNode!=nullptr) {
        declarationNode->SetName(L"villain");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}

void Villain::Update(double elapsed)
{
    Item::Update(elapsed);
    SetLocation(GetX(),GetY()+mSpeedY*elapsed);
    if ((mSpeedY > 0 && GetY() >= GetInitialY()) || (mSpeedY < 0 && GetY() <= GetInitialY()-300))
    {
        mSpeedY = -mSpeedY;
    }

}

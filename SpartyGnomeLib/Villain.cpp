/**
 * @file Villain.cpp
 * 
 * @author Simon Situ, Gabriel Misajlovski, ryanl
 */

#include "pch.h"

#include <string>

#include "Villain.h"

using namespace std;

/// Default Villain Image
const wstring villainImageName = L"UofM.png";

/**
 * Villain Constructor
 * @param game The game holding this item
 */
Villain::Villain(Game* game) : Item(game, villainImageName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration node for this Villain
 * @param item the item node for this Villain
 * @param game The Game this Item is apart of
 */
Villain::Villain(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{
    // Set the hitbox length and width for collisions
    this->SetWidth(125);
    this->SetHeight(140);
}

/**
 * Save this item to an XML node
 * @param node1 The parent node we are going to be a child of
 * @param node2 The second parent node we are going to be a child of
 * @return 1-2 nodes that were added to the XML file
 */
std::pair<wxXmlNode*, wxXmlNode*> Villain::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    // Pull nodes from Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Edit attributes to make the nodes match Villain class
    itemNode->SetName(L"villain");
    itemNode->DeleteAttribute(L"width");
    itemNode->DeleteAttribute(L"height");

    // If current Villain Declaration Node does not exist
    if (declarationNode!=nullptr) {
        // Change declaration node name to villain
        declarationNode->SetName(L"villain");
        return make_pair(itemNode, declarationNode);
    }

    return make_pair(itemNode, nullptr);
}

/**
 * Special Update function for villain movement
 * @param elapsed time elapsed
 */
void Villain::Update(double elapsed)
{
    // Perform Item::Update
    Item::Update(elapsed);

    // Handler for Villain movement
    SetLocation(GetX(),GetY()+mSpeedY*elapsed);
    if ((mSpeedY > 0 && GetY() >= GetInitialY()-15) || (mSpeedY < 0 && GetY() <= GetInitialY()-300))
    {
        mSpeedY = -mSpeedY;
    }

}

/**
 * Give game over when running into a villain
 * @param item the item collided with
 */
void Villain::OnCollision(Item* item){
    this->GetGame()->DisplayLoseMessage();
}

/**
 * @file PlatformF.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Game.h"
#include "PlatformF.h"

using namespace std;

class Game;

/**
 * Testing Constructor
 * @param game Game this item is a member of
 */
PlatformF::PlatformF(Game* game)
        :Platform(game)
{
}

/**
 * Xml Load constructor
 * @param declaration declarationNode to pull from
 * @param item itemNode to pull from
 * @param game The Game that this item is apart of
 */
PlatformF::PlatformF(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Platform(declaration, item, game)
{
}

/**
 * Save this to 1-2 xml nodes
 * @param node1 The parent items node we are adding a child to
 * @param node2 The parent declarations node we are adding a child to
 * @return 1-2 xml nodes that were added
 */
pair<wxXmlNode*,wxXmlNode*> PlatformF::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    // Pull pair from Platform::XmlSave
    auto platformDoubleNode = Platform::XmlSave(node1, node2);

    // Change the type of the itemNode to platformf
    platformDoubleNode.first->SetName(L"platformf");

    // Return the added nodes
    // 1 node if Platform::XmlSave saved 1 node
    // 2 nodes if Platform::XmlSave saved 2 nodes
    return platformDoubleNode;
}

/**
 * Draw this PlatformF
 * @param gc grpahics context to draw on
 */
void PlatformF::Draw(shared_ptr<wxGraphicsContext> gc)
{
    // Draws same as a normal Platform
    Platform::Draw(gc);
}


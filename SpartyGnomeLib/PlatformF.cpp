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

PlatformF::PlatformF(const wxXmlNode* declaration, const wxXmlNode* item)
        :Platform(declaration, item)
{
}

pair<wxXmlNode*,wxXmlNode*> PlatformF::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto platformDoubleNode = Platform::XmlSave(node1, node2);

    platformDoubleNode.first->SetName(L"platformf");

    return platformDoubleNode;
}

void PlatformF::Draw(shared_ptr<wxGraphicsContext> gc)
{
    Platform::Draw(gc);
}


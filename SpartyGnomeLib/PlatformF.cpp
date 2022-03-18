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

// The default duration in seconds if a duration is not specified
const double DefaultDuration = 0;

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
    item->GetAttribute("duration", to_wstring(DefaultDuration)).ToDouble(&mDuration);
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

/**
 * Update function for this item
 * @param elapsed The time in seconds from the last update call
 */
void PlatformF::Update(double elapsed)
{
    Item::Update(elapsed);
    // Start subtracting from mDuration after collision
    if (mLandedUpon)
    {
        // Reduce mDuration by the time elapsed since last update
        mDuration -= elapsed;
        // Remove this item if mDuration is negative
        if (mDuration < 0)
        {
            GetGame()->RemoveItem(this);
        }
    }

}

/**
 * Function to call on collision
 * @param item The item this item collided with
 */
void PlatformF::OnCollision(Item* item)
{
    double itemLeft = item->GetX() - item->GetWidth() / 2;
    double itemRight = itemLeft + item->GetWidth();
    double itemBottom = item->GetY() + item->GetHeight() / 2;
    double platformLeft = GetX() - GetWidth() / 2;
    double platformRight = platformLeft + GetWidth();
    double platformTop = GetY() - GetHeight() / 2;
    bool itemPastLeft = itemRight > platformLeft;
    bool itemBeforeRight = itemLeft < platformRight;

    // If the item hits its head on the bottom of the platform,
    // the distance shouldn't be less than the height of the item.
    // Using half of the item height to be safe
    bool itemAbove = abs(itemBottom - platformTop) < item->GetHeight() / 2;

    if (itemAbove && itemPastLeft && itemBeforeRight)
    {
        mLandedUpon = true;
    }
}


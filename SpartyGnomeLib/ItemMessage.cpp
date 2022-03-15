/**
 * @file ItemMessage.cpp
 *
 * @author Simon Situ
 */

#include "ItemMessage.h"
#include "wx/graphics.h"
#include "Game.h"

const wxColour TextColor(50, 50, 200);
const wxFont TextFont(wxSize(10, 120),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);

/**
 * Constructor for the message
 * @param game The game this message is apart of
 * @param message The message to display
 * @param duration The number of seconds to keep the message displayed
 * @param x The x location of the center of this message
 * @param y The y location of the center of this message
 */
ItemMessage::ItemMessage(Game* game, const std::wstring& message, double duration)
        : Item(game)
{
    mGame = game;
    mMessage = message;
    mDuration = duration;
}

/**
 * Draws this message item
 * @param gc The graphics context to draw on
 */
void ItemMessage::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    double width = 0;
    double height = 0;
    gc->SetFont(TextFont, TextColor);
    //Get the text width and height
    gc->GetTextExtent(mMessage, &width, &height);

    double centerX = GetX() - width / 2;
    double centerY = GetY() - height / 2;
    gc->DrawText(mMessage, centerX, centerY);
}

/**
 * The update function for this message
 * @param elapsed The number of seconds since the last update
 */
void ItemMessage::Update(double elapsed)
{
    mDuration -= elapsed;
    if (mDuration <= 0)
    {
        //Delete this message
        GetGame()->RemoveItem(this);
    }
}

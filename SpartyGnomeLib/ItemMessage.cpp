


/**
 * @file ItemMessage.cpp
 *
 * @author Simon Situ
 */

#include "pch.h"

#include <wx/graphics.h>

#include "ItemMessage.h"
#include "Game.h"

using namespace std;

/// Default Text color
const int DefaultRed = 50;
const int DefaultGreen = 50;
const int DefaultBlue = 200;

/// Default Font specifications
const int DefaultPixelWidth = 10;
const int DefaultPixelHeight = 120;
const auto FontFamily = wxFONTFAMILY_SWISS;
const auto FontStyle = wxFONTSTYLE_NORMAL;
const auto FontWeight = wxFONTWEIGHT_NORMAL;

/**
 * Constructor for the message
 * @param game The game this message is apart of
 * @param message The message to display
 * @param duration The number of seconds to keep the message displayed
 */
ItemMessage::ItemMessage(Game* game, const wstring& message, double duration)
        : Item(game)
{
    mMessage = message;
    mDuration = duration;
    SetColor(DefaultRed, DefaultGreen, DefaultBlue);
    SetFontSize(DefaultPixelWidth, DefaultPixelHeight);
}

/**
 * Draws this message item
 * @param gc The graphics context to draw on
 */
void ItemMessage::Draw(shared_ptr<wxGraphicsContext> gc)
{
    // default width and height
    double width = 0;
    double height = 0;

    // Set the text font and color
    gc->SetFont(mFont, mColor);
    // Get the text width and height
    gc->GetTextExtent(mMessage, &width, &height);

    // Get the center of the text item and draw the item
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
    if (!mPauseDuration)
    {
        mDuration -= elapsed;
        if (mDuration <= 0)
        {
            //Delete this message
            GetGame()->RemoveItem(this);
        }
    }
}

/**
 * Set the font size of the message to display
 * @param pixelWidth The width to draw for each pixel of the font
 * @param pixelHeight The height to draw for each pixel of the font
 */
void ItemMessage::SetFontSize(int pixelWidth, int pixelHeight)
{
    wxSize fontSize(pixelWidth, pixelHeight);
    mFont = wxFont(fontSize, FontFamily, FontStyle, FontWeight);
}

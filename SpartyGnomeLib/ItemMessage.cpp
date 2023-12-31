/**
 * @file ItemMessage.cpp
 *
 * @author Simon Situ, ryanl
 */

#include "pch.h"

#include <wx/graphics.h>

#include "ItemMessage.h"
#include "Game.h"

using namespace std;

/// Default Red color
const int DefaultRed = 50;
/// Default Green color
const int DefaultGreen = 50;
/// Default Blue color
const int DefaultBlue = 200;

/// Default Font Width
const int DefaultPixelWidth = 10;
/// Default Font Height
const int DefaultPixelHeight = 120;
/// Default Font Family
const auto FontFamily = wxFONTFAMILY_SWISS;
/// Default Font Style
const auto FontStyle = wxFONTSTYLE_NORMAL;
/// Default Font Weight
const auto FontWeight = wxFONTWEIGHT_NORMAL;

/**
 * Constructor for the message
 * @param game The game this message is apart of
 * @param message The message to display
 * @param duration The number of seconds to keep the message displayed
 */
ItemMessage::ItemMessage(Game* game, const std::wstring& message, double duration)
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
void ItemMessage::SetFontSize(double pixelWidth, double pixelHeight)
{
    mFontPixelWidth = pixelWidth;
    mFontPixelHeight = pixelHeight;
    wxSize fontSize(mFontPixelWidth, mFontPixelHeight);
    mFont = wxFont(fontSize, FontFamily, FontStyle, FontWeight);
}

/**
 * Getter for the font pixel width
 * @return The font pixel width
 */
double ItemMessage::GetFontWidth()
{
    return mFontPixelWidth;
}

/**
 * Getter for the font pixel height
 * @return The font pixel height
 */
double ItemMessage::GetFontHeight()
{
    return mFontPixelHeight;
}

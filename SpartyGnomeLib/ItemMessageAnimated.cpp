/**
 * @file ItemMessageAnimated.cpp
 * 
 * @author Simon Situ
 */

#include "ItemMessageAnimated.h"

/**
 * The constructor for this animated message
 * @param game The pointer to the game that this item apart of
 * @param message The message to display
 * @param duration The duration of the message
 * @param fontWidth The width of each pixel of the font
 * @param fontHeight The height of each pixel of the font
 */
ItemMessageAnimated::ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
        int fontWidth, int fontHeight)
        : ItemMessage(game, message, duration)
{
    ItemMessage::SetFontSize(fontWidth, fontHeight);
}


/**
 * The velocity constructor
 * @param game The game that this item is apart of
 * @param message The message to display
 * @param duration The duration of the message
 * @param fontWidth The width of each pixel of the font
 * @param fontHeight The height of each pixel of the font
 * @param velocity The velocity of the message
 */
ItemMessageAnimated::ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
        int fontWidth, int fontHeight, Vector velocity)
    :ItemMessageAnimated(game, message, duration, fontWidth, fontHeight)
{
    mVelocity = velocity;
    ItemMessage::SetColor(56,91,67);
}

/**
 * The velocity and acceleration constructor
 * @param game The game that this item is apart of
 * @param message The message to display
 * @param duration The duration of the message
 * @param fontWidth The width of each pixel of the font
 * @param fontHeight The height of each pixel of the font
 * @param velocity The velocity of the message
 * @param acceleration The acceleration of the message
 */
ItemMessageAnimated::ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
        int fontWidth, int fontHeight, Vector velocity, Vector acceleration)
        :ItemMessageAnimated(game, message, duration, fontWidth, fontHeight, velocity)
{
    mAcceleration = acceleration;
    ItemMessage::SetColor(57,149,32);
}

/**
 * The update function
 * @param elapsed The time in seconds since last update
 */
void ItemMessageAnimated::Update(double elapsed)
{
    ItemMessage::Update(elapsed);
    auto newX = GetX() + mVelocity.X() * elapsed;
    auto newY = GetY() + mVelocity.Y() * elapsed;
    // Update position
    SetLocation(newX, newY);
    // Update velocity
    mVelocity += mAcceleration * elapsed;

    // Update size
    SetFontSize(GetFontWidth() + mSizeChange.X(), GetFontHeight() + mSizeChange.Y());
}

/**
 * Setter for the velocity vector
 * @param v The new velocity vector
 */
void ItemMessageAnimated::SetVelocity(const Vector& v)
{
    mVelocity = v;
}

/**
 * Setter for the acceleration vector
 * @param a The new acceleration vector
 */
void ItemMessageAnimated::SetAcceleration(const Vector& a)
{
    mAcceleration = a;
}

/**
 * Setter for the size change vector
 * @param s The new size change vector
 */
void ItemMessageAnimated::SetSizeChange(const Vector& s)
{
    mSizeChange = s;
}

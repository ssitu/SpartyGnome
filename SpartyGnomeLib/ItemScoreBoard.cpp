
/**
 * @file ItemScoreBoard.cpp
 *
 * @author Cameron O'Connor
 */

#include "pch.h"
#include "Game.h"
#include "ItemScoreBoard.h"




/// Font Constants
const int FontWidth = 10;
const int FontHeight = 50;

/// Screen Position Constants
const int ScreenX = 400;
const int ScreenY = 50;

/**
 * The constructor for the timer
 * @param game The Game this item is apart of
 */
ItemScoreBoard::ItemScoreBoard(Game* game)
        : ItemMessage(game, FormatTime(), 0)
{
    ItemMessage::PauseDuration(true);
    ItemMessage::SetFontSize(FontWidth, FontHeight);
    // Do an empty update to set up the message and timer correctly
    Update(0);
}

/**
 * Create a formatted string for time stored
 * @return The formatted string
 */
std::wstring ItemScoreBoard::FormatTime()
{
    std::wstring score = std::to_wstring((int)mScore);
    // Pad with zero

    score = L"$ " + score;





    return score;
}

/**
 * Increment the time by the given seconds
 * @param seconds The time to add to the stored time
 */
 void ItemScoreBoard::IncrementScore(){
     mScore+=100;
 }



/**
 * Update function for this item
 * @param elapsed The time in seconds since last update call
 */
void ItemScoreBoard::Update(double elapsed)
{
    ItemMessage::Update(elapsed);

    ItemMessage::SetMessage(FormatTime());
//    auto gnome = GetGame()->GetGnome();
//    auto gnomeX = gnome->GetX();
//    auto scale = GetGame()->GetScale();
//    auto centerX = 400 / scale;
//    SetLocation(gnomeX - centerX, 100);
    auto newX = GetGame()->GetScreenToWorldX(ScreenX);
    auto newY = ScreenY;
    SetLocation(newX, newY);
}
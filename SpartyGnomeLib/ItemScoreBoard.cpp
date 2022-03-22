
/**
 * @file ItemScoreBoard.cpp
 *
 * @author Cameron O'Connor
 */

#include "pch.h"
#include "Game.h"
#include "ItemScoreBoard.h"


/// Constant Font Width
const int FontWidth = 10;
/// Constant Font Height
const int FontHeight = 50;
/// Font red value
const int FontRed = 112;
/// Font green value
const int FontGreen = 147;
/// Font blue value
const int FontBlue = 219;

/// Screen X Position
const int ScreenX = 400;
/// Screen Y Position
const int ScreenY = 50;

/**
 * The constructor for the scoreboard
 * @param game The Game this item is apart of
 */
ItemScoreBoard::ItemScoreBoard(Game* game)
        : ItemMessage(game, FormatScore(), 0)
{
    ItemMessage::PauseDuration(true);
    ItemMessage::SetFontSize(FontWidth, FontHeight);
    ItemMessage::SetColor(FontRed,FontGreen,FontBlue);
    // Do an empty update to set up the message position
    Update(0);
}

/**
 * Create a formatted string for score stored
 * @return The formatted string
 */
std::wstring ItemScoreBoard::FormatScore()
{
    std::wstring score = std::to_wstring((int)mScore);
    score = L"$ " + score;
    return score;
}

/**
 * Increment the score
 * @param score The score to add to the count
 */
 void ItemScoreBoard::IncrementScore(int score)
 {
     mScore += score;
 }



/**
 * Update function for this item
 * @param elapsed The time in seconds since last update call
 */
void ItemScoreBoard::Update(double elapsed)
{
    ItemMessage::Update(elapsed);
    ItemMessage::SetMessage(FormatScore());
    auto newX = GetGame()->GetScreenToWorldX(ScreenX);
    auto newY = ScreenY;
    SetLocation(newX, newY);
}
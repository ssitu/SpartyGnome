/**
 * @file ItemLevelTimer.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "Game.h"
#include "ItemLevelTimer.h"

/// Constant for Seconds in a minute
const double SecondsInMinute = 60;
/// Constant for Minutes in an hour
const int MinutesInHour = 60;
/// Constant for Hours in a day
const int HoursInDay = 24;

/// Constant Font Width size
const int FontWidth = 10;
/// Constant Font Height size
const int FontHeight = 50;

/// Screen X size
const int ScreenX = -400;
/// Screen Y size
const int ScreenY = 50;

/// Font red value
const int FontRed = 112;
/// Font green value
const int FontGreen = 147;
/// Font blue value
const int FontBlue = 219;

/// Unit of time width in digits
const int Padding = 2;

/**
 * The constructor for the timer
 * @param game The Game this item is apart of
 */
ItemLevelTimer::ItemLevelTimer(Game* game)
        : ItemMessage(game, FormatTime(), 0)
{
    ItemMessage::PauseDuration(true);
    ItemMessage::SetFontSize(FontWidth, FontHeight);
    ItemMessage::SetColor(FontRed,FontGreen,FontBlue);
    // Do an empty update to set up the message and timer correctly
    Update(0);
}

/**
 * Create a formatted string for time stored
 * @return The formatted string
 */
std::wstring ItemLevelTimer::FormatTime()
{
    std::wstring seconds = std::to_wstring((int)mSeconds);
    // Pad with zero
    if (seconds.size() < Padding)
    {
        seconds = L"0" + seconds;
    }

    std::wstring minutes = std::to_wstring(mMinutes) + L":";

    // Add hours if there are hours
    std::wstring hours = L"";
    if (mHours > 0)
    {
        hours = std::to_wstring(mHours) + L":";
    }

    // Add days if there are days
    std::wstring days = L"";
    if (mDays > 0)
    {
        days = std::to_wstring(mDays) + L":";
    }

    return days + hours + minutes + seconds;
}

/**
 * Increment the time by the given seconds
 * @param seconds The time to add to the stored time
 */
void ItemLevelTimer::IncrementTime(double seconds)
{
    mSeconds += seconds;
    if (mSeconds >= SecondsInMinute)
    {
        mSeconds -= SecondsInMinute;
        mMinutes++;
    }
    if (mMinutes >= MinutesInHour)
    {
        mMinutes -= MinutesInHour;
        mHours++;
    }
    if (mHours >= HoursInDay)
    {
        mHours -= HoursInDay;
        mDays++;
    }
}

/**
 * Update function for this item
 * @param elapsed The time in seconds since last update call
 */
void ItemLevelTimer::Update(double elapsed)
{
    ItemMessage::Update(elapsed);
    IncrementTime(elapsed);
    ItemMessage::SetMessage(FormatTime());
    auto newX = GetGame()->GetScreenToWorldX(ScreenX);
    auto newY = ScreenY;
    SetLocation(newX, newY);
}

/**
 * @file ItemLevelTimer.h
 * 
 * @author Simon Situ
 *
 * Displays the time counted via item updates
 */

#ifndef SPARTYGNOME_ITEMLEVELTIMER_H
#define SPARTYGNOME_ITEMLEVELTIMER_H

#include "ItemMessage.h"

/**
 * Displays the time counted via item updates
 */
class ItemLevelTimer : public ItemMessage {
private:
    /// The seconds component of the time
    double mSeconds = 0;
    /// The minutes component of the time
    int mMinutes = 0;
    /// The hours component of the time
    int mHours = 0;
    /// The days component of the time
    int mDays = 0;

    std::wstring FormatTime();
    void IncrementTime(double seconds);

public:
    ItemLevelTimer(Game* game);
    void Update(double elapsed) override;

};

#endif //SPARTYGNOME_ITEMLEVELTIMER_H

/**
 * @file ItemScoreBoard.h
 * @author Cameron O'Connor
 *
 * The scoreboard item
 */

#ifndef SPARTYGNOME_ITEMSCOREBOARD_H
#define SPARTYGNOME_ITEMSCOREBOARD_H

#include "ItemMessage.h"

/**
 * The item that will display the money score on the screen
 */
class ItemScoreBoard : public ItemMessage {
private:
    /// The score count
    double mScore = 0;

    std::wstring FormatScore();

public:
    ItemScoreBoard(Game* game);
    void Update(double elapsed) override;
    void IncrementScore(int score);
};


#endif //SPARTYGNOME_ITEMSCOREBOARD_H

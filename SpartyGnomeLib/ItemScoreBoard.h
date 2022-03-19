/**
 * @file ItemScoreBoard.h
 * @author Cameron O'Connor
 *
 *
 */

#ifndef SPARTYGNOME_ITEMSCOREBOARD_H
#define SPARTYGNOME_ITEMSCOREBOARD_H

#include "ItemMessage.h"
/**
 * The item that will display a message on the screen
 */


class ItemScoreBoard : public ItemMessage {
private:
    /// The seconds component of the time
    double mScore = 0;


    std::wstring FormatTime();
    void IncrementScore();

public:
    ItemScoreBoard(Game* game);
    void Update(double elapsed) override;

};


#endif //SPARTYGNOME_ITEMSCOREBOARD_H

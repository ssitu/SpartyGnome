/**
 * @file Game.h
 * @author Gabriel Misajlovski
 *
 * Initialization of Game Class
 */

#ifndef SPARTYGNOME_GAME_H
#define SPARTYGNOME_GAME_H

#include "Item.h"

class Game {
private:
    double mScale;

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;

public:
    // Constructor
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);

};

#endif //SPARTYGNOME_GAME_H

/**
 * @file Game.h
 * @author Gabriel Misajlovski
 *
 * Initialization of Game Class
 */

#ifndef SPARTYGNOME_GAME_H
#define SPARTYGNOME_GAME_H

#include "Item.h"
#include "ItemSpartyGnome.h"
#include "Platform.h"

class Game {
private:
    double mScale;

    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;

    /// Pointer to the gnome, given at level load
    std::shared_ptr<ItemSpartyGnome> mGnome = nullptr;

public:
    /// Constructor
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, wxDC* dc);

    void Update(double elapsed);

    void Add(std::shared_ptr<Item> item);
    void AddGnome(std::shared_ptr<ItemSpartyGnome> item);

};

#endif //SPARTYGNOME_GAME_H

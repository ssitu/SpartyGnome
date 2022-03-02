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

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Pointer to the gnome, given at level load
    std::shared_ptr<ItemSpartyGnome> mGnome = nullptr;

public:
    /// Constructor
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);
    void NewOrder(std::shared_ptr<Item> mGrabbedItem);
    std::shared_ptr<Item>HitTest(int x, int y);

    void Add(std::shared_ptr<Item> item, double x, double y);
    void AddGnome(std::shared_ptr<ItemSpartyGnome> item);

    std::shared_ptr<ItemSpartyGnome> GetGnome() { return mGnome; }

};

#endif //SPARTYGNOME_GAME_H

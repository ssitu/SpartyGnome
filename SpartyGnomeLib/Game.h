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
    /// The scale for items when drawing
    double mScale;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Pointer to the gnome, given at level load
    std::shared_ptr<ItemSpartyGnome> mGnome = nullptr;

    long mStartY = 512;       ///<gnome x start location in pixels
    long mStartX = 512;       ///<gnome y start location in pixels

    /// Number of seconds to freeze the game for
    double mFreeze = 0;

    void LoadXmlItem(const std::unordered_map<wxString, wxXmlNode*>& declarations_table, const wxXmlNode* item);

    void Accept(ItemVisitor* visitor);

public:
    /// Constructor
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);
    void NewOrder(std::shared_ptr<Item> grabbedItem);
    std::shared_ptr<Item>HitTest(int x, int y);

    void Add(std::shared_ptr<Item> item);
    void Add(std::shared_ptr<Item> item, double x, double y);
    void AddGnome(std::shared_ptr<ItemSpartyGnome> item);
    void Clear();

    void LevelLoad(const std::wstring& filename);
    void LevelLoad(int levelNum);
    void LevelLoadDefault();

    std::shared_ptr<ItemSpartyGnome> GetGnome() { return mGnome; }

    void Save(const wxString &filename);

    /**
     * Returns the number of items loaded in the game
     * @return The number of items
     */
    unsigned int GetNumItems() { return mItems.size(); }

    std::vector<std::shared_ptr<Item>> GetItems() { return mItems; }

    std::shared_ptr<Item> VerticalCollisionTest(Item* item);

    void Freeze(double seconds);

    void DisplayStartMessage(int levelNum);

    void RemoveItem(Item* item);
};

#endif //SPARTYGNOME_GAME_H

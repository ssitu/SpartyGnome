/**
 * @file Game.h
 * @author Gabriel Misajlovski, SimonSitu, ryanl, ashrey, Connor
 *
 * Initialization of Game Class
 */

#ifndef SPARTYGNOME_GAME_H
#define SPARTYGNOME_GAME_H

#include "Item.h"
#include "ItemSpartyGnome.h"
#include "Platform.h"
#include <map>

class Game {
private:
    /// The scale for items when drawing
    double mScale;

    /// A member to hold the level number for reloading levels upon death
    int mLevelNum;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;
    /// All of the images
    std::map<const std::wstring, std::shared_ptr<wxImage>> mImages;
    /// all bitmaps
    std::map<const std::wstring, std::shared_ptr<wxBitmap>> BitMaps;

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

    /**
     * Returns pointer to the gnome object of the game
     * @return Pointer to the gnome object of the game
     */
    std::shared_ptr<ItemSpartyGnome> GetGnome() { return mGnome; }

    /**
     * Returns the number of items loaded in the game
     * @return The number of items
     */
    unsigned int GetNumItems() { return mItems.size(); }

    /**
     * Returns the vector of pointers to items loaded in the game
     * @return The vector of pointers to items
     */
    std::vector<std::shared_ptr<Item>> GetItems() { return mItems; }

    /**
     * Freezes the game for the given amount of time in seconds
     * @param seconds Number of seconds to freeze the game for
     */
    void Freeze(double seconds){ mFreeze = seconds; }

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



    int GetLevelNum() {return mLevelNum;}
    void SetLevelNum(int levelNumber){mLevelNum = levelNumber;}
    void Save(const wxString &filename);
    std::shared_ptr<Item> VerticalCollisionTest(Item* item);
    std::shared_ptr<wxBitmap> GetBitmap(const std::wstring &filename);
    void FreezeScreenMessage(const std::wstring& message);
    void DisplayStartMessage(int levelNum);
    void RemoveItem(Item* item);
    void DisplayLoseMessage();

    void HorizontalCollisionTest(Item* item);
};

#endif //SPARTYGNOME_GAME_H

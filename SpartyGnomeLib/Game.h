/**
 * @file Game.h
 * @author Gabriel Misajlovski, SimonSitu, ryanl, ashrey, Connor
 *
 * The game class that will manage game logic and hold items
 */

#ifndef SPARTYGNOME_GAME_H
#define SPARTYGNOME_GAME_H

#include "Item.h"
#include "ItemSpartyGnome.h"
#include "Platform.h"
#include <map>

/**
 * The game class to hold items and game logic
 */
class Game {
private:
    /// The scale for items when drawing
    double mScale;

    /// A member to hold the level number for reloading levels upon death
    int mLevelNum;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// A mapping from filenames to images
    std::map<const std::wstring, std::shared_ptr<wxImage>> mImages;

    /// A mapping from filenames to bitmaps
    std::map<const std::wstring, std::shared_ptr<wxBitmap>> mBitmaps;

    /// Pointer to the gnome
    std::shared_ptr<ItemSpartyGnome> mGnome = nullptr;

    /// Pointer to the level scoreboard
    std::shared_ptr<ItemScoreBoard> mBoard = nullptr;

    long mStartY = 512;       ///<gnome x start location in pixels
    long mStartX = 512;       ///<gnome y start location in pixels

    /// Number of seconds to freeze the game for
    double mFreeze = 0;

    /// Number of seconds to freeze the game for after a lose or win
    double mFreezeLoseWin = 0;

    /// Bool indicating a loss
    bool mLost = false;

    /// Bool indicated a win
    bool mWin = false;

    void LoadXmlItem(const std::unordered_map<wxString, wxXmlNode*>& declarations_table, const wxXmlNode* item);

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

    /**
     * Freezes the lose/win screen for the given amount of time in seconds
     * @param seconds Number of seconds to freeze the game for
     */
    void FreezeLoseWin(double seconds){ mFreezeLoseWin = seconds; }

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Update(double elapsed);
    void Add(std::shared_ptr<Item> item);
    void Add(std::shared_ptr<Item> item, double x, double y);
    void Clear();
    void LevelLoad(const std::wstring& filename);
    void LevelLoad(int levelNum);
    void LevelLoadDefault();
    void Reset();
    void Setup();
    int GetScreenToWorldX(int x);

    /**
     * Get the current level
     * @return int value of the level
     */
    int GetLevelNum() {return mLevelNum;}

    /**
     * Set the current level
     * @param levelNumber int value of the level to be changed to
     */
    void SetLevelNum(int levelNumber){mLevelNum = levelNumber;}
    void Save(const wxString &filename);
    std::shared_ptr<Item> SolidCollisionTest(Item* item);
    std::shared_ptr<wxBitmap> GetBitmap(const std::wstring &filename);
    void FreezeScreenMessage(const std::wstring& message);
    void DisplayStartMessage(int levelNum);
    void RemoveItem(Item* item);
    void DisplayLoseMessage();
    void DisplayWinMessage();
    void InteractableCollisionTest(Item* item);
    void IncrementScore(int change);
    void Accept(ItemVisitor* visitor);
    int GetGameAreaHeight();
};

#endif //SPARTYGNOME_GAME_H

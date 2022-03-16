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
#include <map>

class Game {
private:
    /// The scale for items when drawing
    double mScale;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;
    /// All of the images
    std::map<const std::wstring, std::shared_ptr<wxImage>> mImages;
    /// all bitmaps
    std::map<const std::wstring, std::shared_ptr<wxBitmap>> mMaps;

    /// Need a way to store the id with its respective information for that item type
    /// Using hashtable to map ids to its respective XML node
    std::unordered_map<wxString, wxXmlNode*> mDeclarations;

    /// Pointer to the gnome, given at level load
    std::shared_ptr<ItemSpartyGnome> mGnome = nullptr;

    long mStartY = 512;       ///<gnome x start location
    long mStartX = 512;       ///<gnome y start location

    void LoadXmlItem(const std::unordered_map<wxString, wxXmlNode*>& declarations_table, const wxXmlNode* item);

    void Accept(ItemVisitor* visitor);

public:
    /// Constructor
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);
    void NewOrder(std::shared_ptr<Item> mGrabbedItem);
    std::shared_ptr<Item>HitTest(int x, int y);

    void Add(std::shared_ptr<Item> item);
    void Add(std::shared_ptr<Item> item, double x, double y);
    void AddGnome(std::shared_ptr<ItemSpartyGnome> item);
    void Clear();

    void LevelLoad(const wxString& filename);

    std::shared_ptr<ItemSpartyGnome> GetGnome() { return mGnome; }

    std::map<const std::wstring , std::shared_ptr<wxImage>>* GetMimages() { return &mImages; }

    std::map<const std::wstring, std::shared_ptr<wxBitmap>> * GetMmaps() { return &mMaps; }

    void Save(const wxString &filename);

    /**
     * Returns the number of items loaded in the game
     * @return The number of items
     */
    unsigned int GetNumItems() { return mItems.size(); }

    std::shared_ptr<Item> VerticalCollisionTest(Item* item);

};

#endif //SPARTYGNOME_GAME_H

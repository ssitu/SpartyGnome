/**
 * @file Item.h
 * @author Gabriel Misajlovski
 *
 * Declaration of Item Class
 */

#ifndef SPARTYGNOME_ITEM_H
#define SPARTYGNOME_ITEM_H

#include <memory>

class Game;

/**
 * Declaration of Item Class
 */
class Item {
private:
    /// The game this item is contained in
    Game *mGame;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    std::wstring mId = L"i000";

protected:
    /**
     * A variable to pass down to derived classes.
     *
     * @param game game the item is in
     * @param filename name of the file saving to or loading from
     */
    Item(Game *game, const std::wstring &filename);
    /// The underlying image
//    std::unique_ptr<wxImage> mItemImage;
    std::shared_ptr<wxImage> mItemImage;
    std::shared_ptr<wxImage> mItemImage2;
    std::shared_ptr<wxImage> mItemImage3;
    /// The bitmap we can display for this item
//    std::unique_ptr<wxBitmap> mItemBitmap;
    std::shared_ptr<wxBitmap> mItemBitmap;
    std::shared_ptr<wxBitmap> mItemBitmap2;
    std::shared_ptr<wxBitmap> mItemBitmap3;

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    virtual ~Item();

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * The width of the item
     * @return Width of image in pixels
     */
    double GetWidth() const { return mItemImage->GetWidth(); }

    /**
     * The height of the item
     * @return Width of image in pixels
     */
    double GetHeight() const { return mItemImage->GetHeight(); }

    void Draw(std::shared_ptr<wxGraphicsContext> gc);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game* GetGame() { return mGame; }

    virtual wxXmlNode* XmlSave(wxXmlNode *node);

    /**
     * Test this item to see if it has been clicked on
     * @param x X location on the game to test in pixels
     * @param y Y location on the game to test in pixels
     * @return true if clicked on
     */
    bool HitTest(int x, int y);

    Item(const wxXmlNode* declaration, const wxXmlNode* item);
};

#endif //SPARTYGNOME_ITEM_H

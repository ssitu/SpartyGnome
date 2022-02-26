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
protected:
    /**
     * A variable to pass down to derived classes.
     *
     * @param game game the item is in
     * @param filename name of the file saving to or loading from
     */
    Item(Game *game, const std::wstring &filename);

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
private:
    /// The aquarium this item is contained in
    Game *mGame;

    /// The underlying image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

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
    void Update(double elapsed) {}
};

#endif //SPARTYGNOME_ITEM_H

/**
 * @file Item.h
 * @author Gabriel Misajlovski
 *
 * Declaration of Item Class
 */

#ifndef SPARTYGNOME_ITEM_H
#define SPARTYGNOME_ITEM_H

#include <memory>
#include "ItemVisitor.h"

class Game;

/**
 * Declaration of Item Class
 */
class Item {
private:
    /// The game this item is contained in
    Game *mGame;

    /// Path of the image file
    std::wstring mPath;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The width of this item
    double mWidth = 0;

    /// The height of this item
    double mHeight = 0;

    /// The XML id of this item
    std::wstring mId = L"i000";

    /// The image for this item
    std::shared_ptr<wxImage> mItemImage;

    /// The bitmap for this item
    std::shared_ptr<wxBitmap> mItemBitmap;

protected:
    Item(Game *game, const std::wstring &filename);

    /**
     * this is a constructor strictly for testing purposes of Platform
     *
     * @author Gabriel Misajlovski
     *
     * @param game game the item is in
     * @param filename left image
     * @param filename2 mid image
     * @param filename3 right image
     */
    Item(Game* game, const std::wstring &filename, const std::wstring &filename2, const std::wstring &filename3)
            : mGame(game) {}

    /**
     * Get the image for this item
     * @return The item image
     */
    std::shared_ptr<wxImage> GetImage() {return mItemImage;}

    /**
     * Set the image for this item
     * @param image
     */
    void SetImage(const std::shared_ptr<wxImage>& image) {mItemImage = image;}

    /**
     * Set the image for this item
     * @param image
     */
    std::wstring GetPath(const std::shared_ptr<wxImage>& image) { return mPath; }

    /**
     * Get the bitmap for this item
     * @return The item bitmap
     */
    std::shared_ptr<wxBitmap> GetBitmap() {return mItemBitmap;}

    /**
     * Set the bitmap for this item
     * @param bitmap
     */
    void SetBitmap(const std::shared_ptr<wxBitmap>& bitmap) {mItemBitmap = bitmap;}

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
    double GetWidth() const { return mWidth; }

    /**
     * The height of the item
     * @return Width of image in pixels
     */
    double GetHeight() const { return mHeight; }

    /// ID getter
    std::wstring GetId() const { return mId; }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);

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

    virtual void SetWidth(double width) { mWidth = width; }

    virtual void SetHeight(double height) { mHeight = height; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game* GetGame() { return mGame; }

    virtual std::pair<wxXmlNode*, wxXmlNode*> XmlSave(wxXmlNode *node1, wxXmlNode *node2);

    /**
     * Test this item to see if it has been clicked on
     * @param x X location on the game to test in pixels
     * @param y Y location on the game to test in pixels
     * @return true if clicked on
     */
    virtual bool HitTest(int x, int y);

    Item(const wxXmlNode* declaration, const wxXmlNode* item);

    virtual void Accept(ItemVisitor* visitor) = 0;
};

#endif //SPARTYGNOME_ITEM_H

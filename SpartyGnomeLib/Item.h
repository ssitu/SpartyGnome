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


    /// Path of the image file
    std::wstring mPath;

    /// Check if grounded or not
    bool mGrounded = true;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
    double  mInitialX = 0;     ///< X Initial (for movement calculations)
    double  mInitialY = 0;     ///< Y Initial (for movement calculations)

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
    Game *mGame;
    // Constructors
    Item(Game *game, const std::wstring &filename);
    Item(Game *game);
    Item(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

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
     * @param image the image for this item
     */
    void SetImage(const std::shared_ptr<wxImage>& image) {mItemImage = image;}

    /**
     * Getter for the image path for this item
     * @return path to the image file
     */
    std::wstring GetPath() { return mPath; }

    /**
     * Getter for the image path for this item
     * @return path to the image file
     */
    void SetPath(const std::wstring& path) { mPath = path; }

    /**
     * Get the bitmap for this item
     * @return The item bitmap
     */
    std::shared_ptr<wxBitmap> GetBitmap() {return mItemBitmap;}

    /**
     * Set the bitmap for this item
     * @param bitmap the bitmap for this item
     */
    void SetBitmap(const std::shared_ptr<wxBitmap>& bitmap) {mItemBitmap = bitmap;}

    /**
     * Set the initial X position for this item
     * @param x The new initial x
     */
     void SetInitialX(double x) {mInitialX = x;}

    /**
    * Set the initial Y position for this item
    * @param y The new initial y
    */
    void SetInitialY(double y) {mInitialY = y;}

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
     * The Y initial location of the item
     * @return Y initial location in pixels
     */
    double GetInitialY() const { return mInitialY; }

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

    /**
     * The imageId of the item
     * @return image Id as a wstring
     */
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

    /**
     * Set the item width
     * @param width item width in pixels
     */
    virtual void SetWidth(double width) { mWidth = width; }

    /**
     * Set the item height
     * @param height item height in pixels
     */
    virtual void SetHeight(double height) { mHeight = height; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game* GetGame() { return mGame; }

    void SetGame(Game* game){mGame = game;}

    virtual std::pair<wxXmlNode*, wxXmlNode*> XmlSave(wxXmlNode *node1, wxXmlNode *node2);
    virtual bool HitTest(int x, int y);
    virtual void Accept(ItemVisitor* visitor) = 0;

    //try adding const
    virtual bool CollisionTest(Item* item);

    virtual void OnCollision(Item* item);
};

#endif //SPARTYGNOME_ITEM_H

/**
 * @file Platform.h
 * @author ryanl, Gabriel Misajlovski
 *
 * Platform Class
 */

#ifndef SPARTYGNOME_PLATFORM_H
#define SPARTYGNOME_PLATFORM_H

#include "Item.h"

/**
 * The platform class
 */
class Platform : public Item {
protected:
    Platform(Game *game, const std::wstring &leftImageFilename, const std::wstring &midImageFilename,
            const std::wstring &rightImageFilename);

private:
    /// The bitmap for the middle segment
    std::shared_ptr<wxBitmap> mMidBitmap;

    /// The bitmap for the middle segment
    std::shared_ptr<wxBitmap> mRightBitmap;

    /// Path of mid image file
    std::wstring mMidPath;

    /// Path of right image file
    std::wstring mRightPath;

public:
    /// Default constructor (disabled)
    Platform() = delete;

    /// Copy constructor (disabled)
    Platform(const Platform &) = delete;

    /// Assignment operator
    void operator=(const Platform &) = delete;

    /// Constructors
    Platform(Game* game);
    Platform(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitPlatform(this);}

    std::pair<wxXmlNode*, wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

};


#endif //SPARTYGNOME_PLATFORM_H

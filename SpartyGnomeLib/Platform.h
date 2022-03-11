/**
 * @file Platform.h
 * @author ryanl, Gabriel Misajlovski
 *
 * Platform Class
 */

#ifndef SPARTYGNOME_PLATFORM_H
#define SPARTYGNOME_PLATFORM_H

#include "Item.h"

class Platform : public Item {
protected:
    Platform(Game *game, const std::wstring &filename, const std::wstring &filename2,
            const std::wstring &filename3);

private:
    /// The image for the middle segment
    std::shared_ptr<wxImage> mMidImage;

    /// The bitmap for the middle segment
    std::shared_ptr<wxBitmap> mMidBitmap;

    /// The image for the middle segment
    std::shared_ptr<wxImage> mRightImage;

    /// The bitmap for the middle segment
    std::shared_ptr<wxBitmap> mRightBitmap;

    std::wstring mMidPath;
    std::wstring mRightPath;

public:
    /// Default constructor (disabled)
    Platform() = delete;

    /// Copy constructor (disabled)
    Platform(const Platform &) = delete;

    /// Assignment operator
    void operator=(const Platform &) = delete;

    Platform(Game* game);

    Platform(const wxXmlNode* declaration, const wxXmlNode* item);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    bool Platform::HitTest(int x, int y) { return Item::HitTest(x, y); }

};


#endif //SPARTYGNOME_PLATFORM_H

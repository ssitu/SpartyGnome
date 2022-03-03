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
private:
    std::wstring mLeftImage;
    std::wstring mRightImage;
    std::wstring mMidImage;

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

    void SaveCompositeImage(wxXmlNode* item);

};


#endif //SPARTYGNOME_PLATFORM_H

/**
 * @file BackgroundImage.h
 * 
 * @author Simon Situ
 *
 * The class for the background item
 */

#ifndef SPARTYGNOME_BACKGROUNDIMAGE_H
#define SPARTYGNOME_BACKGROUNDIMAGE_H

#include "Item.h"

/**
 * The class for the background item
 */
class BackgroundImage : public Item {
public:
    /// disabled default constructor
    BackgroundImage() = delete;

    /// disabled copy
    BackgroundImage(const BackgroundImage&) = delete;

    /// disabled assignment
    void operator=(const BackgroundImage&) = delete;

    /// New constructor
    BackgroundImage(Game* game);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    /// XML constructor
    BackgroundImage(const wxXmlNode* declaration, const wxXmlNode* item);

};

#endif //SPARTYGNOME_BACKGROUNDIMAGE_H

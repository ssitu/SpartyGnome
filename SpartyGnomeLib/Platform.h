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

};


#endif //SPARTYGNOME_PLATFORM_H

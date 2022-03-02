/**
 * @file Villain.h
 * 
 * @author Simon Situ
 *
 * The villain class
 */

#ifndef SPARTYGNOME_VILLAIN_H
#define SPARTYGNOME_VILLAIN_H

#include "Item.h"

/**
 * The villain class
 */
class Villain : public Item {
private:

public:
    /// Disable defaults
    Villain() = delete;
    Villain(const Villain&) = delete;
    void operator=(const Villain&) = delete;

    Villain(Game* game, const std::wstring& imagePath);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //SPARTYGNOME_VILLAIN_H

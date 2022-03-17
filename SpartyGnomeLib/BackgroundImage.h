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

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitBackground(this);}

    BackgroundImage(const wxXmlNode* declaration, const wxXmlNode* item);
    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
};

#endif //SPARTYGNOME_BACKGROUNDIMAGE_H

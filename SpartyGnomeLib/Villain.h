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

    std::pair<wxXmlNode*, wxXmlNode*> XmlSave(wxXmlNode *node1, wxXmlNode *node2) override;

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitVillain(this);}

};

#endif //SPARTYGNOME_VILLAIN_H

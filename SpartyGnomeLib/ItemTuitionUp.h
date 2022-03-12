/**
 * @file ItemTuitionUp.h
 * @author Gabriel Misajlovski
 *
 *
 */

#ifndef SPARTYGNOME_ITEMTUITIONUP_H
#define SPARTYGNOME_ITEMTUITIONUP_H

#include "Item.h"

class ItemTuitionUp : public Item {
public:
    /// disabled default constructor
    ItemTuitionUp() = delete;

    /// disabled copy
    ItemTuitionUp(const ItemTuitionUp&) = delete;

    /// disabled assignment
    void operator=(const ItemTuitionUp&) = delete;

    /// New constructor
    ItemTuitionUp(Game* game);

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    /// XML constructor
    ItemTuitionUp(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitTuitionUp(this);}

};

#endif //SPARTYGNOME_ITEMTUITIONUP_H

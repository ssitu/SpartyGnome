/**
 * @file ItemTuitionUp.h
 * @author Gabriel Misajlovski
 *
 * TuitionUp Class
 */

#ifndef SPARTYGNOME_ITEMTUITIONUP_H
#define SPARTYGNOME_ITEMTUITIONUP_H

#include "Item.h"

/**
 * TuitionUp class
 */
class ItemTuitionUp : public Item {
public:
    /// disabled default constructor
    ItemTuitionUp() = delete;

    /// disabled copy
    ItemTuitionUp(const ItemTuitionUp&) = delete;

    /// disabled assignment
    void operator=(const ItemTuitionUp&) = delete;

    /// New constructors
    ItemTuitionUp(Game* game);
    ItemTuitionUp(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitTuitionUp(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
};

#endif //SPARTYGNOME_ITEMTUITIONUP_H

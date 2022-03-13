/**
 * @file ItemDoor.h
 * @author ashre, Gabriel Misajlovski
 *
 *
 */

#ifndef SPARTYGNOME_ITEMDOOR_H
#define SPARTYGNOME_ITEMDOOR_H

#include "Item.h"

class ItemDoor : public Item {
public:
    /// disabled default constructor
    ItemDoor() = delete;

    /// disabled copy
    ItemDoor(const ItemDoor&) = delete;

    /// disabled assignment
    void operator=(const ItemDoor&) = delete;

    /// New constructor
    ItemDoor(Game* game);

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    /// XML constructor
    ItemDoor(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitDoor(this);}

    bool CollisionTest(Item* item);
};

#endif //SPARTYGNOME_ITEMDOOR_H

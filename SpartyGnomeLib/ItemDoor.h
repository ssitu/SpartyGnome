/**
 * @file ItemDoor.h
 * @author ashre, Gabriel Misajlovski
 *
 * ItemDoor Class
 */

#ifndef SPARTYGNOME_ITEMDOOR_H
#define SPARTYGNOME_ITEMDOOR_H

#include "Item.h"

/**
 * ItemDoor Class
 */
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

    /// XML constructor
    ItemDoor(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitDoor(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
    bool CollisionTest(Item* item);

};

#endif //SPARTYGNOME_ITEMDOOR_H

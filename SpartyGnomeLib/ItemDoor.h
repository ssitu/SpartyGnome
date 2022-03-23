/**
 * @file ItemDoor.h
 * @author ashre, Gabriel Misajlovski, ryanl
 *
 *
 */

#ifndef SPARTYGNOME_ITEMDOOR_H
#define SPARTYGNOME_ITEMDOOR_H

#include "Item.h"
#include "Game.h"
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
    ItemDoor(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitDoor(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    /**
     * Checks if there is a collision between the gnome and the door
     * @param item door within the level
     * @return bool true or false
     */
    bool CollisionTest(Item* item) override;

    /**
     * Function that handles what happens when the gnome touches the door successfully
     * @param item door within the level
     */
    virtual void OnCollision(Item* item) override;
};

#endif //SPARTYGNOME_ITEMDOOR_H

/**
 * @file ItemMoney.h
 * @author mgabr
 *
 *
 */

#ifndef SPARTYGNOME_ITEMMONEY_H
#define SPARTYGNOME_ITEMMONEY_H

#include "Item.h"

class ItemMoney : public Item {
public:
    /// disabled default constructor
    ItemMoney() = delete;

    /// disabled copy
    ItemMoney(const ItemDoor&) = delete;

    /// disabled assignment
    void operator=(const ItemMoney&) = delete;

    /// New constructor
    ItemMoney(Game* game);

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    /// XML constructor
    ItemMoney(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitMoney(this);}
};

#endif //SPARTYGNOME_ITEMMONEY_H

/**
 * @file ItemMoney.h
 * @author mgabr
 *
 * ItemMoney class
 */

#ifndef SPARTYGNOME_ITEMMONEY_H
#define SPARTYGNOME_ITEMMONEY_H

#include "Item.h"

/**
 * ItemMoney class
 */
class ItemMoney : public Item {
private:
    /// How much this money item is worth upon collection
    double mValue = 0;

public:
    /// disabled default constructor
    ItemMoney() = delete;

    /// disabled copy
    ItemMoney(const ItemDoor&) = delete;

    /// disabled assignment
    void operator=(const ItemMoney&) = delete;

    /// New constructor
    ItemMoney(Game* game);
    ItemMoney(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitMoney(this);}


    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
};

#endif //SPARTYGNOME_ITEMMONEY_H

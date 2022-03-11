/**
 * @file ItemDoor.h
 * @author ashre
 *
 *
 */

#ifndef SPARTYGNOME_ITEMDOOR_H
#define SPARTYGNOME_ITEMDOOR_H

#include "Item.h"

class ItemDoor : public Item {
private:

public:

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitDoor(this);}
};

#endif //SPARTYGNOME_ITEMDOOR_H

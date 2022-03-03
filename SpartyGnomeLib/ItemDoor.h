/**
 * @file ItemDoor.h
 * @author ashre
 *
 *
 */

#ifndef SPARTYGNOME_ITEMDOOR_H
#define SPARTYGNOME_ITEMDOOR_H

#include "Item.h"

class ItemDoor : Item {
private:

public:

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //SPARTYGNOME_ITEMDOOR_H

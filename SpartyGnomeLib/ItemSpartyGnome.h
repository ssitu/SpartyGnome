/**
 * @file ItemSpartyGnome.h
 * @author ashre
 *
 *
 */

#ifndef SPARTYGNOME_ITEMSPARTYGNOME_H
#define SPARTYGNOME_ITEMSPARTYGNOME_H

#include "Item.h"

class ItemSpartyGnome : public Item {
private:

public:
    /// Default constructor (disabled)
    ItemSpartyGnome() = delete;

    /// Copy constructor (disabled)
    ItemSpartyGnome(const ItemSpartyGnome &) = delete;

    /// Assignment operator
    void operator=(const ItemSpartyGnome &) = delete;

    ItemSpartyGnome(Game* game);

};

#endif //SPARTYGNOME_ITEMSPARTYGNOME_H

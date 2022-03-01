/**
 * @file ItemSpartyGnome.h
 * @author ashre
 *
 *
 */

#ifndef SPARTYGNOME_ITEMSPARTYGNOME_H
#define SPARTYGNOME_ITEMSPARTYGNOME_H

#include "Vector.h"
#include "Item.h"

class ItemSpartyGnome : public Item {
private:
    Vector mV;

    bool mGravityEnable = false;

public:
    /// Default constructor (disabled)
    ItemSpartyGnome() = delete;

    /// Copy constructor (disabled)
    ItemSpartyGnome(const ItemSpartyGnome &) = delete;

    /// Assignment operator
    void operator=(const ItemSpartyGnome &) = delete;

    ItemSpartyGnome(Game* game);

    void Jump();

    void Update(double elapsed);

};

#endif //SPARTYGNOME_ITEMSPARTYGNOME_H

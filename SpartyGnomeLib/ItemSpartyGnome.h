/**
 * @file ItemSpartyGnome.h
 * @author ashre, Gabriel Misajlovski
 *
 * The class for our Gnome
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

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitGnome(this);}

    void DisableGravity() { mGravityEnable = false; };

};

#endif //SPARTYGNOME_ITEMSPARTYGNOME_H

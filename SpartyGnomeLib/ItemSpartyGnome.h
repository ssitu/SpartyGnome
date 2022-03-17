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
    /// Vector containing both current X and Y velocities of Gnome
    Vector mV;

    /// Is gravity enabled? This will tell you.
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
    void MoveRight();
    void MoveLeft();
    void StopMove();

    void Update(double elapsed) override;

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitGnome(this);}

    /// Gravity Functions.
    void DisableGravity() { mGravityEnable = false; }
    void EnableGravity() { mGravityEnable = true; }

    bool GravityCheck(){return mGravityEnable;}
    void AnimateGnomeRight();
    void AnimateGnomeLeft();
    void AnimateStop();

};

#endif //SPARTYGNOME_ITEMSPARTYGNOME_H

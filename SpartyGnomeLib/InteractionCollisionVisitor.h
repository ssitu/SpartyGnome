/**
 * @file InteractionCollisionVisitor.h
 * @author ashrey gupta
 *
 * The collision visitor for checking for collision testing with interactables
 */

#ifndef SPARTYGNOME_INTERACTIONCOLLISIONVISITOR_H
#define SPARTYGNOME_INTERACTIONCOLLISIONVISITOR_H

#include "CollisionVisitor.h"

/**
 * The collision visitor for checking for collision testing with interactables
 */
class InteractionCollisionVisitor: public CollisionVisitor {
private:

public:
    InteractionCollisionVisitor(Item* item);
    void VisitDoor(ItemDoor* door) override;
    void VisitPlatformF(PlatformF* platformF) override;

    void VisitVillain(Villain* villain);

    void VisitTuitionUp(ItemTuitionUp* tu);

    void VisitMoney(ItemMoney* money);
};

#endif //SPARTYGNOME_INTERACTIONCOLLISIONVISITOR_H

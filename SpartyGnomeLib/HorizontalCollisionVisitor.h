/**
 * @file HorizontalCollisionVisitor.h
 * @author ashrey gupta
 *
 *
 */

#ifndef SPARTYGNOME_HORIZONTALCOLLISIONVISITOR_H
#define SPARTYGNOME_HORIZONTALCOLLISIONVISITOR_H

#include "CollisionVisitor.h"

class HorizontalCollisionVisitor: public CollisionVisitor {
private:

public:
    HorizontalCollisionVisitor(Item* item);
    void VisitDoor(ItemDoor* door) override;
    void VisitPlatformF(PlatformF* platformF) override;

    void VisitVillain(Villain* villain);

    void VisitTuitionUp(ItemTuitionUp* tu);

    void VisitMoney(ItemMoney* money);
};

#endif //SPARTYGNOME_HORIZONTALCOLLISIONVISITOR_H

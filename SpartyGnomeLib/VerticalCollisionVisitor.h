/**
 * @file VerticalCollisionVisitor.h
 * 
 * @author Simon Situ
 *
 * Visitor to handle vertical collisions
 */

#ifndef SPARTYGNOME_VERTICALCOLLISIONVISITOR_H
#define SPARTYGNOME_VERTICALCOLLISIONVISITOR_H

#include "CollisionVisitor.h"

class VerticalCollisionVisitor : public CollisionVisitor {
private:

public:
    VerticalCollisionVisitor(Item* item);
    void VisitWall(Wall* wall) override;
    void VisitPlatform(Platform* platform) override;
    void VisitPlatformF(PlatformF* platformF) override;

};

#endif //SPARTYGNOME_VERTICALCOLLISIONVISITOR_H

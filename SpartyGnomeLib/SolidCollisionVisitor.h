/**
 * @file SolidCollisionVisitor.h
 * 
 * @author Simon Situ
 *
 * Visitor to test collisions with solid objects
 */

#ifndef SPARTYGNOME_SOLIDCOLLISIONVISITOR_H
#define SPARTYGNOME_SOLIDCOLLISIONVISITOR_H

#include "CollisionVisitor.h"

/**
 * Visitor that tests collisions with solid objects
 */
class SolidCollisionVisitor : public CollisionVisitor {
public:
    SolidCollisionVisitor(Item* item);
    void VisitWall(Wall* wall) override;
    void VisitPlatform(Platform* platform) override;
    void VisitPlatformF(PlatformF* platformF) override;
};

#endif //SPARTYGNOME_SOLIDCOLLISIONVISITOR_H

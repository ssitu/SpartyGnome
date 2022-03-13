/**
 * @file VerticalCollisionVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "VerticalCollisionVisitor.h"
#include "Wall.h"
#include "Platform.h"

/**
 * Vertical collision test for wall
 * @param wall Wall to test
 */
void VerticalCollisionVisitor::VisitWall(Wall* wall)
{
    CollisionVisitor::CollisionTest(*wall);
}

/**
 * Vertical collision test for platform
 * @param platform Wall to test
 */
void VerticalCollisionVisitor::VisitPlatform(Platform* platform)
{
    CollisionVisitor::CollisionTest(*platform);
}

/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
VerticalCollisionVisitor::VerticalCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{

}

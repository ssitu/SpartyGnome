/**
 * @file VerticalCollisionVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"

#include "VerticalCollisionVisitor.h"
#include "Wall.h"
#include "Platform.h"
#include "PlatformF.h"

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
 * Vertical collision test for platform
 * @param platform Wall to test
 */
void VerticalCollisionVisitor::VisitPlatformF(PlatformF* platformF)
{
    CollisionVisitor::CollisionTest(*platformF);
}

/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
VerticalCollisionVisitor::VerticalCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{

}

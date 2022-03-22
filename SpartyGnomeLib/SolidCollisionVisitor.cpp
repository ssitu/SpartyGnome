/**
 * @file SolidCollisionVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"

#include "SolidCollisionVisitor.h"
#include "Wall.h"
#include "Platform.h"
#include "PlatformF.h"

/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
SolidCollisionVisitor::SolidCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{
}

/**
 * Vertical collision test for wall
 * @param wall Wall to test
 */
void SolidCollisionVisitor::VisitWall(Wall* wall)
{
    CollisionVisitor::CollisionTest(wall);
    CollisionVisitor::OnCollision(wall);
}

/**
 * Vertical collision test for platform
 * @param platform Platform to test
 */
void SolidCollisionVisitor::VisitPlatform(Platform* platform)
{
    CollisionVisitor::CollisionTest(platform);
    CollisionVisitor::OnCollision(platform);
}

/**
 * Vertical collision test for platformf
 * @param platformF PlatformF to test
 */
void SolidCollisionVisitor::VisitPlatformF(PlatformF* platformF)
{
    CollisionVisitor::CollisionTest(platformF);
    CollisionVisitor::OnCollision(platformF);
}



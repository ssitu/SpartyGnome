/**
 * @file HorizontalCollisionVisitor.cpp
 * @author ashre
 */
#include "pch.h"
#include "HorizontalCollisionVisitor.h"
#include "ItemDoor.h"
#include "Villain.h"
#include "PlatformF.h"

/**
 * Collision Test for door
 * @param platform door to test
 */
void HorizontalCollisionVisitor::VisitDoor(ItemDoor* door)
{
    CollisionVisitor::CollisionTest(door);
}

void HorizontalCollisionVisitor::VisitVillain(Villain* villain) {
    CollisionVisitor::CollisionTest(villain);
}
/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
HorizontalCollisionVisitor::HorizontalCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{

}

/**
 * Test collisions with a PlatformF
 * @param platformF The platformF to test collisions with
 */
void HorizontalCollisionVisitor::VisitPlatformF(PlatformF* platformF)
{
    CollisionVisitor::CollisionTest(platformF);
}

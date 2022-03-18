/**
 * @file HorizontalCollisionVisitor.cpp
 * @author ashre
 */
#include "pch.h"
#include "HorizontalCollisionVisitor.h"
#include "ItemDoor.h"

/**
 * Collision Test for door
 * @param platform door to test
 */
void HorizontalCollisionVisitor::VisitDoor(ItemDoor* door)
{
    CollisionVisitor::CollisionTest(door);
}


/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
HorizontalCollisionVisitor::HorizontalCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{

}

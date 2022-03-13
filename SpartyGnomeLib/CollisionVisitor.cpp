/**
 * @file CollisionVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "CollisionVisitor.h"
#include "Item.h"

/**
 * The constructor for the visitor
 * @param item The item to check collisions with
 */
CollisionVisitor::CollisionVisitor(Item* item)
{
    mItem = item;
}

/**
 * Indicates if the last collision check determined a collision
 * @return True if the last test determined a collision, false otherwise
 */
bool CollisionVisitor::IsColliding()
{
    auto result = mCollision;
    //Reset the bool
    mCollision = false;
    return result;
}

/**
 * Performs a collision test with the given item and the stored item
 * @param item Item to test with
 */
void CollisionVisitor::CollisionTest(const Item& item)
{
    mCollision = item.CollisionTest(mItem);
}

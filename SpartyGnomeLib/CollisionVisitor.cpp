/**
 * @file CollisionVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"

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
void CollisionVisitor::CollisionTest(Item* item)
{
    mCollision = item->CollisionTest(mItem);
}

/**
 * Calls the given item's OnCollision function if there is a collision
 * @param item The item to call OnCollision on if a collision test has tested true
 */
void CollisionVisitor::OnCollision(Item* item)
{
    if (mCollision)
    {
        item->OnCollision(mItem);
    }
}

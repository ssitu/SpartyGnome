/**
 * @file CollisionVisitor.h
 * 
 * @author Simon Situ
 *
 * Visitor to handle collision tests
 */

#ifndef SPARTYGNOME_COLLISIONVISITOR_H
#define SPARTYGNOME_COLLISIONVISITOR_H

#include "ItemVisitor.h"

class Item;

/**
 * Visitor to handle collision tests
 */
class CollisionVisitor : public ItemVisitor {
private:
    /// Indicates if the last collision test was a collision
    bool mCollision = false;

    /// The item to test collisions with
    Item* mItem;

protected:
    void CollisionTest(Item* item);

public:
    CollisionVisitor(Item* item);
    bool IsColliding();

};

#endif //SPARTYGNOME_COLLISIONVISITOR_H

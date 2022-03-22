/**
 * @file InteractionCollisionVisitor.cpp
 * @author ashre
 */
#include "pch.h"
#include "InteractionCollisionVisitor.h"
#include "ItemDoor.h"
#include "Villain.h"
#include "PlatformF.h"
#include "ItemTuitionUp.h"
#include "ItemMoney.h"

/**
 * Collision Test for Door
 * @param door Door to test
 */
void InteractionCollisionVisitor::VisitDoor(ItemDoor* door)
{
    CollisionVisitor::CollisionTest(door);
}

/**
 * Collision Test for Villain
 * @param villain Villain to test
 */
void InteractionCollisionVisitor::VisitVillain(Villain* villain) {
    CollisionVisitor::CollisionTest(villain);
}

/**
 * Collision Test for ItemTuitionUp
 * @param tu ItemTuitionUp to test
 */
void InteractionCollisionVisitor::VisitTuitionUp(ItemTuitionUp* tu) {
    CollisionVisitor::CollisionTest(tu);
}

/**
 * Collision Test for ItemMoney
 * @param money ItemMoney to test
 */
void InteractionCollisionVisitor::VisitMoney(ItemMoney* money) {
    CollisionVisitor::CollisionTest(money);
}
/**
 * Constructor for this visitor
 * @param item Item to check collisions with
 */
InteractionCollisionVisitor::InteractionCollisionVisitor(Item* item)
        :CollisionVisitor(item)
{

}

/**
 * Test collisions with a PlatformF
 * @param platformF The platformF to test collisions with
 */
void InteractionCollisionVisitor::VisitPlatformF(PlatformF* platformF)
{
    CollisionVisitor::CollisionTest(platformF);
}

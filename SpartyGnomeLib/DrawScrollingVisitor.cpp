/**
 * @file DrawScrollingVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "DrawScrollingVisitor.h"
#include "Villain.h"
#include "Platform.h"
#include "Wall.h"
#include "ItemDoor.h"

/**
 * The constructor for the visitor
 * @param gc The graphics context
 */
DrawScrollingVisitor::DrawScrollingVisitor(std::shared_ptr<wxGraphicsContext> gc)
{
    mGraphicsContext = gc;
}

/**
 * Visit a villain
 * @param villain Villain to visit
 */
void DrawScrollingVisitor::VisitVillain(Villain* villain)
{
    villain->Draw(mGraphicsContext);
}

/**
 * Visit a platform
 * @param platform Platform to visit
 */
void DrawScrollingVisitor::VisitPlatform(Platform* platform)
{
    platform->Draw(mGraphicsContext);
}

/**
 * Visit a wall
 * @param wall Wall to visit
 */
void DrawScrollingVisitor::VisitWall(Wall* wall)
{
    wall->Draw(mGraphicsContext);
}

/**
 * Visit a door
 * @param door Door to visit
 */
void DrawScrollingVisitor::VisitDoor(ItemDoor* door)
{
    door->Draw(mGraphicsContext);
}


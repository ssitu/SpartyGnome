/**
 * @file DrawScrollingVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "BackgroundImage.h"
#include "ItemMoney.h"
#include "Villain.h"
#include "Platform.h"
#include "PlatformF.h"
#include "Wall.h"
#include "ItemDoor.h"
#include "ItemTuitionUp.h"
#include "DrawScrollingVisitor.h"
#include "ItemMessage.h"

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
 * Visit a platformF
 * @param platformF Platform to visit
 */
void DrawScrollingVisitor::VisitPlatformF(PlatformF* platformF)
{

    platformF->Draw(mGraphicsContext);

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

/**
 * Visit a Background
 * @param background Background to visit
 */
void DrawScrollingVisitor::VisitBackground(BackgroundImage* background)
{
    background->Draw(mGraphicsContext);
}

/**
 * Visit Money
 * @param money Money to visit
 */
void DrawScrollingVisitor::VisitMoney(ItemMoney* money)
{
    money->Draw(mGraphicsContext);
}

/**
 * Visit TuitionUp
 * @param tuition TuitionUp to visit
 */
void DrawScrollingVisitor::VisitTuitionUp(ItemTuitionUp* tuition)
{
    tuition->Draw(mGraphicsContext);
}

/**
 * Visit ItemMessage
 * @param tuition ItemMessage to visit
 */
void DrawScrollingVisitor::VisitMessage(ItemMessage* message)
{
    message->Draw(mGraphicsContext);
}


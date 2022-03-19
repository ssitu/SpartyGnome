/**
 * @file DrawStaticVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "DrawStaticVisitor.h"
#include "ItemLevelTimer.h"


/**
 * Constructor for this visitor
 * @param gc The graphics context
 */
DrawStaticVisitor::DrawStaticVisitor(std::shared_ptr<wxGraphicsContext> gc)
{
    mGraphicsContext = gc;
}

/**
 * Draws the timer
 * @param timer The timer to draw
 */
void DrawStaticVisitor::VisitItemLevelTimer(ItemLevelTimer* timer)
{
    timer->Draw(mGraphicsContext);
}

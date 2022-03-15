/**
 * @file DrawMessagesVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "DrawMessagesVisitor.h"
#include "ItemMessage.h"

/**
 * Constructor for this visitor
 * @param gc The graphics context
 */
DrawMessagesVisitor::DrawMessagesVisitor(std::shared_ptr<wxGraphicsContext> gc)
{
    mGraphicsContext = gc;
}

/**
 * Draws a message
 * @param message The message to draw
 */
void DrawMessagesVisitor::VisitMessage(ItemMessage* message)
{
    message->Draw(mGraphicsContext);
}

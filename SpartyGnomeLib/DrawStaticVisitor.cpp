/**
 * @file DrawStaticVisitor.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "DrawStaticVisitor.h"
#include "ItemSpartyGnome.h"

/**
 * Constructor for this visitor
 * @param gc The graphics context
 */
DrawStaticVisitor::DrawStaticVisitor(std::shared_ptr<wxGraphicsContext> gc)
{
    mGraphicsContext = gc;
}

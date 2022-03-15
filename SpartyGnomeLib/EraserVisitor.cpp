/**
 * @file EraserVisitor.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"
#include "EraserVisitor.h"
#include "ItemSpartyGnome.h"

/**
 * Constructor for this visitor
 * @param gc The graphics context
 */
EraserVisitor::EraserVisitor(std::shared_ptr<wxGraphicsContext> gc)
{
    mGraphicsContext = gc;
}
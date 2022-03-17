/**
 * @file DrawStaticVisitor.h
 * 
 * @author Simon Situ
 *
 * Visitor class to draw static items
 */

#ifndef SPARTYGNOME_DRAWSTATICVISITOR_H
#define SPARTYGNOME_DRAWSTATICVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor class to draw static items
 */
class DrawStaticVisitor : public ItemVisitor {
private:
    /// The graphics context to draw items
    std::shared_ptr<wxGraphicsContext> mGraphicsContext;

public:
    DrawStaticVisitor(std::shared_ptr<wxGraphicsContext> gc);
};

#endif //SPARTYGNOME_DRAWSTATICVISITOR_H

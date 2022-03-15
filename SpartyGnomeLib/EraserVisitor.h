/**
 * @file EraserVisitor.h
 * @author Gabriel Misajlovski
 *
 * Visitor for erasing items.
 */

#ifndef SPARTYGNOME_ERASERVISITOR_H
#define SPARTYGNOME_ERASERVISITOR_H

#include "ItemVisitor.h"

class EraserVisitor : public ItemVisitor {
private:
    /// The graphics context to draw items
    std::shared_ptr<wxGraphicsContext> mGraphicsContext;

public:
    EraserVisitor(std::shared_ptr<wxGraphicsContext> gc);

};

#endif //SPARTYGNOME_ERASERVISITOR_H

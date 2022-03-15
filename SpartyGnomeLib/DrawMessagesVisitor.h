/**
 * @file DrawMessagesVisitor.h
 * 
 * @author Simon Situ
 *
 * Visitor class to draw message items
 */

#ifndef SPARTYGNOME_DRAWMESSAGEVISITOR_H
#define SPARTYGNOME_DRAWMESSAGEVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor class to draw message items
 */
class DrawMessagesVisitor : public ItemVisitor {
private:
    /// The graphics context to draw items
    std::shared_ptr<wxGraphicsContext> mGraphicsContext;

public:
    DrawMessagesVisitor(std::shared_ptr<wxGraphicsContext> gc);
    void VisitMessage(ItemMessage* message) override;
};

#endif //SPARTYGNOME_DRAWMESSAGEVISITOR_H

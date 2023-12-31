/**
 * @file DrawScrollingVisitor.h
 * 
 * @author Simon Situ, Gabriel Misajlovski
 *
 * The visitor class to draw scrolling items
 */

#ifndef SPARTYGNOME_DRAWSCROLLINGVISITOR_H
#define SPARTYGNOME_DRAWSCROLLINGVISITOR_H

#include "ItemVisitor.h"

/**
 * The visitor class to draw scrolling items
 */
class DrawScrollingVisitor : public ItemVisitor {
private:
    /// The graphics context used to draw the scrolling items
    std::shared_ptr<wxGraphicsContext> mGraphicsContext;

public:
    DrawScrollingVisitor(std::shared_ptr<wxGraphicsContext> gc);
    void VisitVillain(Villain* villain) override;
    void VisitPlatform(Platform* platform) override;
    void VisitPlatformF(PlatformF* platformF) override;
    void VisitWall(Wall* wall) override;
    void VisitDoor(ItemDoor* door) override;
    void VisitBackground(BackgroundImage* background) override;
    void VisitMoney(ItemMoney* money) override;
    void VisitTuitionUp(ItemTuitionUp* tuition) override;
    void VisitMessage(ItemMessage* message) override;

};

#endif //SPARTYGNOME_DRAWSCROLLINGVISITOR_H

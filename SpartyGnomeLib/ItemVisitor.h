/**
 * @file ItemVisitor.h
 * 
 * @author Simon Situ
 *
 * The visitor class for item objects
 */

#ifndef SPARTYGNOME_ITEMVISITOR_H
#define SPARTYGNOME_ITEMVISITOR_H


// Forward references to all item types
class ItemSpartyGnome;
class Platform;
class Wall;
class Villain;
class ItemDoor;
class BackgroundImage;
class ItemMoney;
class ItemTuitionUp;

/**
 * The visitor class for item objects
 */
class ItemVisitor {
private:

public:
    /**
     * Visit a Gnome
     * @param gnome The Gnome to visit
     */
    virtual void VisitGnome(ItemSpartyGnome* gnome) {}

    /**
     * Visit a Platform
     * @param platform The Platform to visit
     */
    virtual void VisitPlatform(Platform* platform) {}

    /**
     * Visit a Wall
     * @param wall The Wall to visit
     */
    virtual void VisitWall(Wall* wall) {}

    /**
     * Visit a Villain
     * @param villain The Villain to visit
     */
    virtual void VisitVillain(Villain* villain) {}

    /**
     * Visit a Door
     * @param door The Door to visit
     */
    virtual void VisitDoor(ItemDoor* door) {}

    /**
     * Visit a Background
     * @param background The Background to visit
     */
    virtual void VisitBackground(BackgroundImage* background) {}

    /**
     * Visit Money
     * @param money The money to visit
     */
    virtual void VisitMoney(ItemMoney* money) {}

    /**
     * Visit TuitionUp
     * @param tu The object to visit
     */
    virtual void VisitTuitionUp(ItemTuitionUp* tu) {}
};

#endif //SPARTYGNOME_ITEMVISITOR_H

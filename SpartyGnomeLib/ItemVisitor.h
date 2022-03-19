/**
 * @file ItemVisitor.h
 * 
 * @author Simon Situ, Gabriel Misajlovski
 *
 * The visitor class for item objects
 */

#ifndef SPARTYGNOME_ITEMVISITOR_H
#define SPARTYGNOME_ITEMVISITOR_H


// Forward references to all item types
class ItemSpartyGnome;
class Platform;
class PlatformF;
class Wall;
class Villain;
class ItemDoor;
class BackgroundImage;
class ItemMoney;
class ItemTuitionUp;
class ItemMessage;
class ItemLevelTimer;
class ItemScoreBoard;
/**
 * The visitor class for item objects
 */
class ItemVisitor {
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
     * Visit a PlatformF
     * @param platformF The PlatformF to visit
     */
    virtual void VisitPlatformF(PlatformF* platformF) {}

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
     * @param money The Money to visit
     */
    virtual void VisitMoney(ItemMoney* money) {}

    /**
     * Visit a TuitionUp
     * @param tu The TuitionUp to visit
     */
    virtual void VisitTuitionUp(ItemTuitionUp* tu) {}

    /**
     * Visit a ItemMessage
     * @param message ItemMessage to visit
     */
    virtual void VisitMessage(ItemMessage* message) {}

    /**
     * Visit a ItemLevelTimer
     * @param timer The ItemLevelTimer to visit
     */
    virtual void VisitItemLevelTimer(ItemLevelTimer* timer) {}

    virtual void VisitItemScoreBoard(ItemScoreBoard* scoreboard) {}
};

#endif //SPARTYGNOME_ITEMVISITOR_H

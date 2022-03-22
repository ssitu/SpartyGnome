/**
 * @file ItemTuitionUp.h
 * @author Gabriel Misajlovski
 *
 * TuitionUp Class
 */

#ifndef SPARTYGNOME_ITEMTUITIONUP_H
#define SPARTYGNOME_ITEMTUITIONUP_H

#include "Item.h"
#include "Game.h"
#include "ItemScoreBoard.h"
#include "ItemMessageAnimated.h"
/**
 * TuitionUp class
 */
class ItemTuitionUp : public Item {
private:
    double mSpeedY = 600;

    bool mTuitionIncrease = false;
    bool mCollided = false;

public:
    /// disabled default constructor
    ItemTuitionUp() = delete;

    /// disabled copy
    ItemTuitionUp(const ItemTuitionUp&) = delete;

    /// disabled assignment
    void operator=(const ItemTuitionUp&) = delete;

    /// New constructors
    ItemTuitionUp(Game* game);
    ItemTuitionUp(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitTuitionUp(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    void OnCollision(Item* item);

    void Update(double elapsed) override;
};

#endif //SPARTYGNOME_ITEMTUITIONUP_H

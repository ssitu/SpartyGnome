/**
 * @file Villain.h
 * 
 * @author Simon Situ, Gabriel Misajlovski
 *
 * The villain class
 */

#ifndef SPARTYGNOME_VILLAIN_H
#define SPARTYGNOME_VILLAIN_H

#include "Item.h"

/**
 * The villain class
 */
class Villain : public Item {
private:
    /// The speed at which a villain moves
    double mSpeedY = -240;

public:
    /// Disable defaults
    Villain() = delete;

    /// disable copy
    Villain(const Villain&) = delete;

    /// Disable = operator
    void operator=(const Villain&) = delete;

    /// New constructors
    Villain(Game* game);
    Villain(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitVillain(this);}

    std::pair<wxXmlNode*, wxXmlNode*> XmlSave(wxXmlNode *node1, wxXmlNode *node2) override;
    void Update(double elapsed) override;

};

#endif //SPARTYGNOME_VILLAIN_H

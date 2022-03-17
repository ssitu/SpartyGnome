/**
 * @file Wall.h
 * @authors cro56, Gabriel Misajlovski
 *
 * Wall Class Header File
 */

#ifndef SPARTYGNOME_WALL_H
#define SPARTYGNOME_WALL_H

#include "Item.h"

/**
 * Wall Class Declaration
 */
class Wall : public Item {
public:
    /// Disable default constructor
    Wall() = delete;

    /// Disable copy
    Wall(const Wall&) = delete;

    /// Disable = Operator
    void operator=(const Wall&) = delete;

    /// New Constructors
    Wall(Game* game);
    Wall(const wxXmlNode* declaration, const wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitWall(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

};

#endif //SPARTYGNOME_WALL_H

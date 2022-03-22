/**
 * @file Wall.h
 * @authors Cameron O'Connor, Gabriel Misajlovski
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
    Wall(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitWall(this);}

    /**
    * Save this item to an XML node
    * @param node The parent node we are going to be a child of
    * @return 1-2 nodes that were added to the XML file
    */
    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;

    /**
    * draws item
    * @param gc Graphics context shared pointer
    */
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

};

#endif //SPARTYGNOME_WALL_H

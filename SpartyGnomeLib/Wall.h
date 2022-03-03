/**
 * @file Wall.h
 * @authors cro56, Gabriel Misajlovski
 *
 * Wall Class Header File
 */

#ifndef SPARTYGNOME_WALL_H
#define SPARTYGNOME_WALL_H

#include "Item.h"

class Wall : public Item {
public:
    /// Disable defaults
    Wall() = delete;
    Wall(const Wall&) = delete;
    void operator=(const Wall&) = delete;

    Wall(Game* game);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //SPARTYGNOME_WALL_H

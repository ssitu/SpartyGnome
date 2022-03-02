/**
 * @file Wall.h
 * @author cro56
 *
 *
 */

#ifndef SPARTYGNOME_WALL_H
#define SPARTYGNOME_WALL_H
#include "Item.h"
class Wall : Item {
private:

public:
    /// Disable defaults
    Wall() = delete;
    Wall(const Wall&) = delete;
    void operator=(const Wall&) = delete;

    Wall(Game* game, const std::wstring& imagePath);

};

#endif //SPARTYGNOME_WALL_H

/**
 * @file BackgroundImage.h
 * 
 * @author Simon Situ
 *
 * The class for the background item
 */

#ifndef SPARTYGNOME_BACKGROUNDIMAGE_H
#define SPARTYGNOME_BACKGROUNDIMAGE_H

#include "Item.h"

/**
 * The class for the background item
 */
class BackgroundImage : public Item {
private:

public:
    /// disabled default constructor
    BackgroundImage() = delete;

    /// disabled copy
    BackgroundImage(const BackgroundImage&) = delete;

    /// disabled assignment
    void operator=(const BackgroundImage&) = delete;

    /// New constructor
    BackgroundImage(Game* game);

};

#endif //SPARTYGNOME_BACKGROUNDIMAGE_H

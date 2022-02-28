/**
 * @file Villain.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include "Villain.h"

/**
 * Villain Constructor
 * @param game The game holding this item
 * @param imagePath The path to the image for this item
 */
Villain::Villain(Game* game, const std::wstring& imagePath) : Item(game, imagePath)
{

}

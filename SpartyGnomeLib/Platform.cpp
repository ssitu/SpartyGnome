/**
 * @file Platform.cpp
 * @author ryanl
 */

#include "pch.h"
#include "Platform.h"
#include <string>
using namespace std;
const wstring PlatformName = L"images/snow.png";

/**
 * Constructor
 * @param game Game this item is a member of
 */
Platform::Platform(Game *game) : Item(game, PlatformName)
{
}


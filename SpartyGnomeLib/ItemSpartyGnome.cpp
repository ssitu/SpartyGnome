/**
 * @file ItemSpartyGnome.cpp
 * @author ryanl, ashrey
 */
#include "pch.h"
#include "ItemSpartyGnome.h"
#include<string>
using namespace std;
const wstring SpartyGnomeImageName = L"images/gnome.png";

/**
 * Constructor
 * @param game Game this item is a member of
 */
ItemSpartyGnome::ItemSpartyGnome(Game *game) : Item(game, SpartyGnomeImageName)
{
}
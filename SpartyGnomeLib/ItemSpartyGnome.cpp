/**
 * @file ItemSpartyGnome.cpp
 * @author ryanl, ashrey
 */
#include "pch.h"
#include "ItemSpartyGnome.h"
#include <string>
using namespace std;
const wstring SpartyGnomeImageName = L"images/gnome.png";

/**
 * Constructor
 * @param game Game this item is a member of
 */
ItemSpartyGnome::ItemSpartyGnome(Game *game) : Item(game, SpartyGnomeImageName)
{
}

void ItemSpartyGnome::Jump()
{
    mSpeedY = -300;
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void ItemSpartyGnome::Update(double elapsed)
{
    SetLocation(GetX(), GetY()+mSpeedY*elapsed);

}
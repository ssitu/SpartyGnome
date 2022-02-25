/**
 * @file Item.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 */
Item::Item(Game *game, const wstring &filename) : mGame(game)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}

/**
 * Draw this fish
 * @param dc Device context to draw on
 */
void Item::Draw(wxDC *dc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    dc->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));
}


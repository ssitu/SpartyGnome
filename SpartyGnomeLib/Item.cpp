/**
 * @file Item.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

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
 * Draw this item
 * @param gc Graphics context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    gc->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2),
            wid + 1,
            hit
            );
}


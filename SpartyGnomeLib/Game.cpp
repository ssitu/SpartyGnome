/**
 * @file Game.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Item.h"
#include "Game.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

const int InitialX = 1024/2;
const int InitialY = 1024/2;

Game::Game()
{
    mBackground = make_unique<wxBitmap>(
            L"images/backgroundForest.png", wxBITMAP_TYPE_ANY);
    //TODO need ItemSpartyGnome finished
//    mGnome = std::make_shared<ItemSpartyGnome>(this);
//    mItems.push_back(mGnome);
}


/**
 * Draw the game area
 * @param graphics The wxWidgets graphics context on which to draw
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height, wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)width/mScale;
    graphics->PushState();

    //
    // Draw in virtual pixels on the graphics context
    //

    // Draw static items


    // Draw scrolling items
    // TODO: ItemSpartyGnome needs to call the Item constructor so that GetX() can be called
//    auto xOffset = (double)-mGnome->GetX() + virtualWidth / 2.0f;
//    graphics->Translate(xOffset, 0);
//    for (const auto& item : mItems)
//    {
//        item->Draw(graphics);
//    }

    graphics->PopState();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::AddGnome(std::shared_ptr<Item> item)
{
    item->SetLocation(InitialX,InitialY);
    mItems.push_back(item);
}
/**
 * @file ItemSpartyGnome.cpp
 * @author ryanl, ashrey, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "Platform.h"
#include "PlatformF.h"
#include "Game.h"
#include "ItemSpartyGnome.h"
#include "ItemDoor.h"

using namespace std;

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Horizontal character speed in pixels per second
const double HorizontalSpeed = 500.00;

/// vertical initial jump speed
const double JumpSpeed = -800;

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

/// Default SpartyGnomeImage
const wstring SpartyGnomeImageName = L"gnome.png";

/// Walk left image 1
const wstring SpartyGnomeLeft1 = L"gnome-walk-left-1.png";
/// Walk Left Image 2
const wstring SpartyGnomeLeft2 = L"gnome-walk-left-2.png";
/// Walk Right Image 1
const wstring SpartyGnomeRight1 = L"gnome-walk-right-1.png";
/// Walk Right Image 2
const wstring SpartyGnomeRight2 = L"gnome-walk-right-2.png";
/// Height of gnome image
const int GnomeHeight = 200;
/// Width of Gnome image
const int GnomeWidth = 108;

/**
 * Constructor
 * @param game Game this item is a member of
 */
ItemSpartyGnome::ItemSpartyGnome(Game *game) : Item(game, SpartyGnomeImageName)
{
    // Default Gnome image size used for collision purposes
    this->SetHeight(GnomeHeight);
    this->SetWidth(GnomeWidth);
}

/**
 * Jump Event Handler
 * Make the gnome jump
 */
void ItemSpartyGnome::Jump()
{
    // If the gnome is not moving vertically
    if (mV.Y() == 0)
    {
        // Jump
        mV.SetY(JumpSpeed);
    }
}

/**
 * Move Right Event Handler
 * Move the gnome right
 */
void ItemSpartyGnome::MoveRight()
{
    // If the vector movement is moving towards the right
    if (mV.X() >= 0)
    {
        // Move the gnome right
        mV.SetX(HorizontalSpeed);
    }
}

/**
 * Move Left Event Handler
 * Move the gnome left
 */
void ItemSpartyGnome::MoveLeft()
{
    // If the vector movement is moving towards the left
    if (mV.X() <= 0)
    {
        // Move the gnome left
        mV.SetX(0-HorizontalSpeed);
    }
}

/**
 * Stop Move Event Handler
 * Stop the Gnome
 */
void ItemSpartyGnome::StopMove()
{
    // Stop movement
    mV.SetX(0);
}

/**
 * Update Function
 * Update the gnome
 * @param elapsed time elapsed
 */
void ItemSpartyGnome::Update(double elapsed)
{
    // Call Item::Update
    Item::Update(elapsed);

    // If gravity is enabled...
    if (mGravityEnable)
    {

        // Gravity
        // Compute a new velocity with gravity added in.
        Vector newV(mV.X(), mV.Y()+Gravity*elapsed);
        Vector p(this->GetX(), this->GetY());

        // Update position
        Vector newP = p+newV*elapsed;

        // Animation Controls
        if (newV.X() > 0)
        {
            // Animate the gnome to the right
            AnimateGnomeRight();
        }
        else if (newV.X() < 0)
        {
            // Animate the gnome to the left
            AnimateGnomeLeft();
        }
        else
        {
            // Animate the gnome to idle/default
            AnimateStop();
        }

        // Updating the Y location
        SetLocation(p.X(), newP.Y());

        // Test for collision
        auto collided = GetGame()->SolidCollisionTest(this);
        if (collided != nullptr)
        {
            if (newV.Y()>0)
            {
                // We are falling, stop at the collision point
                newP.SetY(collided->GetY()-collided->GetHeight()/2-GetHeight()/2-Epsilon);

                // Increment counter
                mCount += elapsed;

                // if the counter is >= 0.2, (100 pixels/500 pixel speed = 0.2)
                if (mCount >= 0.2)
                {
                    // Set the counter to 0
                    mCount = mCount-0.2;

                    // set switch to opposite
                    mSwitch = !mSwitch;
                }
            }
            else
            {
                // We are rising, stop at the collision point
                newP.SetY(collided->GetY()+collided->GetHeight()/2+GetHeight()/2+Epsilon);
            }

            // If we collide, we cancel any velocity
            // in the Y direction

            // If you are bonking your head move down a little before finishing Y-axis changes
            if (mV.Y() < 0)
            {
                mV.SetY(-mV.Y());
            }

            // Stop Y motion
            newV.SetY(0);
        }

        // Updating the X location
        SetLocation(newP.X(), p.Y());

        // Test for collision
        collided = GetGame()->SolidCollisionTest(this);
        if (collided != nullptr)
        {
            if (newV.X() > 0)
            {
                // We are moving to the right, stop at the collision point
                newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
            }
            else
            {
                // We are moving to the left, stop at the collision point
                newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
            }

            // If we collide, we cancel any velocity
            // in the X direction
            newV.SetX(0);
            AnimateStop();
        }

        // Update the velocity and position
        mV = newV;
        SetLocation(newP.X(), newP.Y());
    }

    // After all movement updates, check for collisions with non-solid objects
    // In the case that an OnCollision would update the gnome position, it would get overwritten before this point
    GetGame()->InteractableCollisionTest(this);

    // If the current height/position exceeds the death height, Lose
    auto deathHeight = GetGame()->GetGameAreaHeight() + GetHeight() / 2;
    if (GetY() >= deathHeight)
    {
        DisableGravity();
        this->GetGame()->DisplayLoseMessage();
    }
}

/**
 * Animate Right Event Handler
 * Animates Gnome to the Right
 */
void ItemSpartyGnome::AnimateGnomeRight()
{
    std::shared_ptr<wxBitmap> mRight1 = GetGame()->GetBitmap(SpartyGnomeRight1);
    std::shared_ptr<wxBitmap> mRight2 = GetGame()->GetBitmap(SpartyGnomeRight2);

    if (mSwitch)
    {
        SetBitmap(mRight1);
    }
    else
    {
        SetBitmap(mRight2);
    }
}

/**
 * Animate Left Event Handler
 * Animates Gnome to the left
 */
void ItemSpartyGnome::AnimateGnomeLeft()
{
    std::shared_ptr<wxBitmap> mLeft1 = GetGame()->GetBitmap(SpartyGnomeLeft1);
    std::shared_ptr<wxBitmap> mLeft2 = GetGame()->GetBitmap(SpartyGnomeLeft2);

    if (mSwitch)
    {
        SetBitmap(mLeft1);
    }
    else
    {
        SetBitmap(mLeft2);
    }
}

/**
 * Animate Stop Event Handler
 * Animates Gnome to its idle animation
 */
void ItemSpartyGnome::AnimateStop()
{
    std::shared_ptr<wxBitmap> mStop = GetGame()->GetBitmap(SpartyGnomeImageName);
    SetBitmap(mStop);
}

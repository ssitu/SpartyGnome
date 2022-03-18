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
const wstring SpartyGnomeImageName = L"images/gnome.png";

/// Walk left image 1
const wstring SpartyGnomeLeft1 = L"images/gnome-walk-left-1.png";
/// Walk Left Image 2
const wstring SpartyGnomeLeft2 = L"images/gnome-walk-left-2.png";
/// Walk Right Image 1
const wstring SpartyGnomeRight1 = L"images/gnome-walk-right-1.png";
/// Walk Right Image 2
const wstring SpartyGnomeRight2 = L"images/gnome-walk-right-2.png";
/// Height of gnome image
const int GnomeHeight = 200;
/// Width of Gnome image
const int GnomeWidth = 108;
/// the death barrier
const int DeathHeight = 1024;

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
 * @author Gabriel Misajlovski
 */
void ItemSpartyGnome::Jump()
{
    // If the gnome is not moving vertically...
    if (mV.Y() == 0) {
        // Jump
        mV.SetY(JumpSpeed);
    }
}

/**
 * Move Right Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::MoveRight()
{
    // if gnome is not moving horizontally or moving to the
    if (mV.X() >= 0) {
        // move right
        mV.SetX(HorizontalSpeed);
    }

}

/**
 * Move Left Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::MoveLeft()
{
    // if gnome is not moving horizontally or is moving right
    if (mV.X() <= 0) {
        // move left
        mV.SetX(0-HorizontalSpeed);
    }

}

/**
 * Stop Move Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::StopMove()
{
    // Stop movement
    mV.SetX(0);
}

/**
 * Update Function
 * @param elapsed time elapsed
 */
void ItemSpartyGnome::Update(double elapsed)
{
    // Call Item::Update
    Item::Update(elapsed);
    // if switch is true
    if (mSwitch)
    {
        // increment counter
        mCount++;

        // if the counter is >= 5
        if (mCount >= 5)
        {
            // Set the counter to 0
            mCount = 0;

            // set switch to false
            mSwitch = false;
        }
    }
    // If switch is false
    else
    {
        // Counter +=1
        mCount++;

        // if counter >= 5
        if (mCount >= 5)
        {
            // set counter to 0
            mCount = 0;

            // set switch to true
            mSwitch = true;
        }
    }

    // if gravity is enabled...
    if (mGravityEnable) {
        // if the Y velocity is 0...
        if (mV.Y() == 0)
        {
            // Gnome is not jumping
            mCheckJump = false;
        }
        else
        {
            // Gnome is jumping
            mCheckJump = true;
        }

        // Gravity
        // Compute a new velocity with gravity added in.
        Vector newV(mV.X(), mV.Y()+Gravity*elapsed);
        Vector p(this->GetX(), this->GetY());

        // Update position
        Vector newP = p+newV*elapsed;

        // Animation Controls
        if (newV.X() > 0)
        {
            // Moving to the right
            AnimateGnomeRight();
        }
        else if (newV.X() < 0)
        {
            // Moving to the left
            AnimateGnomeLeft();
        }
        else
        {
            // Not moving
            AnimateStop();
        }

        //
        // Try updating the Y location.
        //
        SetLocation(p.X(), newP.Y());

        // Test for collision
        auto collided = GetGame()->VerticalCollisionTest(this);
        if (collided != nullptr)
        {
            if (newV.Y()>0) {
                // We are falling, stop at the collision point
                newP.SetY(collided->GetY()-collided->GetHeight()/2-GetHeight()/2-Epsilon);

            }
            else {
                // We are rising, stop at the collision point
                newP.SetY(collided->GetY()+collided->GetHeight()/2+GetHeight()/2+Epsilon);

            }

            // If we collide, we cancel any velocity
            // in the Y direction
            if (mV.Y()>=0 && collided->IsF()) {
                GetGame()->RemoveItem(collided.get());
            }

            if (mV.Y() < 0) {
                mV.SetY(-mV.Y());
            }

            // Stop Y motion
            newV.SetY(0);

        }

        //
        // Try updating the X location
        //
        SetLocation(newP.X(), p.Y());

        // Test for collision
        collided = GetGame()->VerticalCollisionTest(this);
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

    if (GetY() >= DeathHeight) {
        DisableGravity();
        this->GetGame()->DisplayLoseMessage();
    }
}

/**
 * Animate Right Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::AnimateGnomeRight()
{
    std::shared_ptr<wxBitmap> mRight1 = GetGame()->GetBitmap(SpartyGnomeRight1);
    std::shared_ptr<wxBitmap> mRight2 = GetGame()->GetBitmap(SpartyGnomeRight2);

    // The Gnome is not jumping, changing
    if (!mCheckJump)
    {
        if (mSwitch) {
            SetBitmap(mRight1);
        }
        else {
            SetBitmap(mRight2);
        }
    }
    // The Gnome is jumping, constant
    else
    {
        SetBitmap(mRight1);
    }

}

/**
 * Animate Left Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::AnimateGnomeLeft()
{
    std::shared_ptr<wxBitmap> mLeft1 = GetGame()->GetBitmap(SpartyGnomeLeft1);
    std::shared_ptr<wxBitmap> mLeft2 = GetGame()->GetBitmap(SpartyGnomeLeft2);

    // The Gnome is not jumping, changing
    if (!mCheckJump)
    {
        if (mSwitch) {
            SetBitmap(mLeft1);
        }
        else if (!mSwitch) {
            SetBitmap(mLeft2);
        }
    }

    // The Gnome is not jumping, constant
    else
    {
        SetBitmap(mLeft1);
    }

}

/**
 * Animate Stop Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::AnimateStop()
{
    std::shared_ptr<wxBitmap> mStop = GetGame()->GetBitmap(SpartyGnomeImageName);
    SetBitmap(mStop);
}

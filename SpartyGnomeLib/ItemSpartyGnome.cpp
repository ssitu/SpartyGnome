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

const double JumpSpeed = -800;

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

/// Default SpartyGnomeImage
const wstring SpartyGnomeImageName = L"images/gnome.png";

const wstring SpartyGnomeLeft1 = L"images/gnome-walk-left-1.png";
const wstring SpartyGnomeLeft2 = L"images/gnome-walk-left-2.png";
const wstring SpartyGnomeRight1 = L"images/gnome-walk-right-1.png";
const wstring SpartyGnomeRight2 = L"images/gnome-walk-right-2.png";

/**
 * Constructor
 * @param game Game this item is a member of
 */
ItemSpartyGnome::ItemSpartyGnome(Game *game) : Item(game, SpartyGnomeImageName)
{
    this->SetHeight(200);
    this->SetWidth(108);
}

/**
 * Jump Event Handler
 * @author Gabriel Misajlovski
 */
void ItemSpartyGnome::Jump()
{
    auto collided = GetGame()->VerticalCollisionTest(this);
    if (mV.Y() == 0) {
        mV.SetY(JumpSpeed);
    }
}

/**
 * Move Right Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::MoveRight()
{

    auto collided = GetGame()->VerticalCollisionTest(this);
    if (mV.X() == 0) {
        mV.SetX(HorizontalSpeed);
    }

}

/**
 * Move Left Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::MoveLeft()
{
    auto collided = GetGame()->VerticalCollisionTest(this);
    if (mV.X() == 0) {
        mV.SetX(0-HorizontalSpeed);
    }

}

/**
 * Stop Move Event Handler
 * @author ryanl
 */
void ItemSpartyGnome::StopMove()
{
    auto collided = GetGame()->VerticalCollisionTest(this);
    mV.SetX(0);
}

bool mSwitch = true;
bool mCheckJump = false;
int mCount = 0;
void ItemSpartyGnome::Update(double elapsed)
{
    Item::Update(elapsed);
    if (mSwitch == true)
    {
        mCount++;
        if (mCount >= 5)
        {
            mCount = 0;
            mSwitch = false;
        }
    }
    else if (mSwitch == false)
    {
        mCount++;
        if (mCount >= 5)
        {
            mCount = 0;
            mSwitch = true;
        }
    }
    if (mGravityEnable) {
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

        //
        // Try updating the Y location.
        //
        SetLocation(p.X(), newP.Y());


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
            newV.SetY(0);

            if (collided->IsF()) {
                GetGame()->RemoveItem(collided.get());
            }
        }

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
        // Try updating the X location
        //
        SetLocation(newP.X(), p.Y());

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

    if (GetY() >= 1024) {
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
    if (mCheckJump == false)
    {
        if (mSwitch == true) {
            SetBitmap(mRight1);
        }
        else if (mSwitch == false) {
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
    if (mCheckJump == false)
    {
        if (mSwitch == true) {
            SetBitmap(mLeft1);
        }
        else if (mSwitch == false) {
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

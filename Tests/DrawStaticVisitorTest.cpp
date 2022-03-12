/**
 * @file DrawStaticVisitorTest.cpp
 * @author Simon Situ
 */

#include <pch.h>
#include <memory>

#include <DrawStaticVisitor.h>
#include <Villain.h>
#include <Platform.h>
#include <Wall.h>
#include <ItemDoor.h>
#include <ItemSpartyGnome.h>
#include <Game.h>
#include <BackgroundImage.h>

#include "gtest/gtest.h"

/**
 * Mock class to test the scrolling visitor
 */
class DrawStaticVisitorMock : public DrawStaticVisitor {
public:
    /// Indicates if a gnome has been visited
    bool mVisitedGnome = false;

    DrawStaticVisitorMock() : DrawStaticVisitor(nullptr) {}
    void VisitGnome(ItemSpartyGnome* gnome) override { mVisitedGnome = true; }
};

TEST(DrawStaticVisitorTest, StaticVisit)
{
    auto tempImage = L"images/gnome.png";
    Game* game = new Game();
    Villain villain(game, tempImage);
    Platform platform(game);
    ItemSpartyGnome gnome(game);
    Wall wall(game);
    BackgroundImage background(game);
    //Cannot test door, unfinished class

    DrawStaticVisitorMock visitor;

    villain.Accept(&visitor);
    //Gnome visit should not have been called
    ASSERT_FALSE(visitor.mVisitedGnome);

    platform.Accept(&visitor);
    //Gnome visit should not have been called
    ASSERT_FALSE(visitor.mVisitedGnome);

    wall.Accept(&visitor);
    //Gnome visit should not have been called
    ASSERT_FALSE(visitor.mVisitedGnome);

    background.Accept(&visitor);
    //Gnome visit should not have been called
    ASSERT_FALSE(visitor.mVisitedGnome);

    gnome.Accept(&visitor);
    //Visitor should have drawn the gnome
    ASSERT_TRUE(visitor.mVisitedGnome);
}

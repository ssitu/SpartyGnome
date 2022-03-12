/**
 * @file DrawScrollingVisitorTest.cpp
 * @author Simon Situ
 */

#include <pch.h>
#include <memory>

#include <DrawScrollingVisitor.h>
#include <Villain.h>
#include <Platform.h>
#include <Wall.h>
#include <ItemDoor.h>
#include <Game.h>
#include <BackgroundImage.h>

#include "gtest/gtest.h"

/**
 * Mock class to test the scrolling visitor
 */
class DrawScrollingVisitorMock : public DrawScrollingVisitor {
public:
    /// Indicates if a villain has been visited
    bool mVisitedVillain = false;
    /// Indicates if a platform has been visited
    bool mVisitedPlatform = false;
    /// Indicates if a wall has been visited
    bool mVisitedWall = false;
    /// Indicates if a door has been visited
    bool mVisitedDoor = false;
    /// Indicates if a background has been visited
    bool mVisitedBackground = false;

    DrawScrollingVisitorMock() : DrawScrollingVisitor(nullptr) {}
    void VisitVillain(Villain* villain) override { mVisitedVillain = true; }
    void VisitPlatform(Platform* platform) override { mVisitedPlatform = true; }
    void VisitWall(Wall* wall) override { mVisitedWall = true; }
    void VisitDoor(ItemDoor* door) override { mVisitedDoor = true; }
    void VisitBackground(BackgroundImage* background) override { mVisitedBackground = true; }
};

TEST(DrawScrollingVisitorTest, ScrollingVisit)
{
    auto tempImage = L"images/gnome.png";
    Game* game = new Game();
    Villain villain(game, tempImage);
    Platform platform(game);
    ItemSpartyGnome gnome(game);
    Wall wall(game);
    BackgroundImage background(game);
    //Cannot test door, unfinished class

    DrawScrollingVisitorMock visitor;

    villain.Accept(&visitor);
    //Only villain should have been visited
    ASSERT_TRUE(visitor.mVisitedVillain);
    ASSERT_FALSE(visitor.mVisitedPlatform);
    ASSERT_FALSE(visitor.mVisitedWall);
    ASSERT_FALSE(visitor.mVisitedDoor);
    ASSERT_FALSE(visitor.mVisitedBackground);

    platform.Accept(&visitor);
    //Only villain and platform should have been visited
    ASSERT_TRUE(visitor.mVisitedVillain);
    ASSERT_TRUE(visitor.mVisitedPlatform);
    ASSERT_FALSE(visitor.mVisitedWall);
    ASSERT_FALSE(visitor.mVisitedDoor);
    ASSERT_FALSE(visitor.mVisitedBackground);

    gnome.Accept(&visitor);
    //Gnome should not call any of the other visits
    ASSERT_TRUE(visitor.mVisitedVillain);
    ASSERT_TRUE(visitor.mVisitedPlatform);
    ASSERT_FALSE(visitor.mVisitedWall);
    ASSERT_FALSE(visitor.mVisitedDoor);
    ASSERT_FALSE(visitor.mVisitedBackground);

    wall.Accept(&visitor);
    //Only villain, platform, and wall should be visited
    ASSERT_TRUE(visitor.mVisitedVillain);
    ASSERT_TRUE(visitor.mVisitedPlatform);
    ASSERT_TRUE(visitor.mVisitedWall);
    ASSERT_FALSE(visitor.mVisitedDoor);
    ASSERT_FALSE(visitor.mVisitedBackground);

    background.Accept(&visitor);
    //Only villain, platform, wall, and background should be visited
    ASSERT_TRUE(visitor.mVisitedVillain);
    ASSERT_TRUE(visitor.mVisitedPlatform);
    ASSERT_TRUE(visitor.mVisitedWall);
    ASSERT_FALSE(visitor.mVisitedDoor);
    ASSERT_TRUE(visitor.mVisitedBackground);

}

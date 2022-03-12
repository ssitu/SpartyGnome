/**
 * @file PlatformTest.cpp
 * @author Gabriel Misajlovski
 *
 * Unit tests for Platform Class
 */

#include <pch.h>
#include <memory>
#include <Game.h>
#include <Platform.h>
#include "gtest/gtest.h"

const std::wstring PlatformLeftImage = L"snowLeft.png";
const std::wstring PlatformMidImage = L"snowMid.png";
const std::wstring PlatformRightImage = L"snowRight.png";
const double defaultX = 100;
const double defaultY = 100;
const double defaultWidth = 160;
const double defaultHeight = 32;

/** Mock class for testing the class Platform */
class PlatformMock : public Platform {
public:
    PlatformMock(Game *game) : Platform(game, PlatformLeftImage, PlatformMidImage,
            PlatformRightImage) {}

};

TEST(PlatformTest, HitTest)
{
    Game game;

    PlatformMock platform(&game);

    platform.SetLocation(defaultX, defaultY);
    platform.SetWidth(defaultWidth);
    platform.SetHeight(defaultHeight);

    // Test location where image is not.
    ASSERT_FALSE(platform.HitTest(0,0));

    ASSERT_TRUE(platform.HitTest(defaultX, defaultY));



}
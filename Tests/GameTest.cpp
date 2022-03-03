/**
 * @file GameTest.cpp
 * @author Simon Situ
 *
 * Unit tests for the Game class
 */

#include <pch.h>
#include <memory>
#include <Game.h>
#include <BackgroundImage.h>
#include "gtest/gtest.h"

TEST(GameTest, Clear)
{
    Game game;

    game.Clear();
    // There should still be a gnome
    ASSERT_EQ(game.GetNumItems(), 1);

    std::shared_ptr<BackgroundImage> item = std::make_shared<BackgroundImage>(&game);
    game.Add(item);
    ASSERT_EQ(game.GetNumItems(), 2);

    game.Clear();
    ASSERT_EQ(game.GetNumItems(), 1);
}
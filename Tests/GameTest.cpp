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

TEST(GameTest, CollisionTest)
{
    Game game;
    //Get the items
    std::shared_ptr<BackgroundImage> item = std::make_shared<BackgroundImage>(&game);
    game.Add(item);

    //Place gnome in the center of every coordinate in the item's area
    auto startX = item->GetX() - item->GetWidth() / 2;
    auto startY = item->GetY() - item->GetHeight() / 2;
    for (double x = startX; )
}
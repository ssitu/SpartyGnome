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
#include <Platform.h>
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

TEST(GameTest, VerticalCollisionTest)
{
    Game game;
    //Get the items
    std::shared_ptr<ItemSpartyGnome> gnome = game.GetGnome();
    std::shared_ptr<Platform> item = std::make_shared<Platform>(&game);

    item->SetWidth(100);
    item->SetHeight(100);
    game.Add(item);

    //Place gnome in the center of every coordinate in the item's area
    int startX = item->GetX() - item->GetWidth() / 2;
    int startY = item->GetY() - item->GetHeight() / 2;
    int endX = item->GetX() + item->GetWidth() / 2;
    int endY = item->GetY() + item->GetHeight() / 2;
    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            gnome->SetLocation(x, y);
            ASSERT_EQ(item, game.VerticalCollisionTest(gnome.get()));
        }
    }

    //Test no collisions
    const int PixelsToTest = 100;
    for (int x = endX + gnome->GetWidth(); x < endX + gnome->GetWidth() + PixelsToTest; x++)
    {
        for (int y = endY + gnome->GetHeight(); y < endY + gnome->GetHeight() + PixelsToTest; y++)
        {
            gnome->SetLocation(x, y);
            auto collision = game.VerticalCollisionTest(gnome.get());
            ASSERT_EQ(nullptr, collision);
        }
    }
}
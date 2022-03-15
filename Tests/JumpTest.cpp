/**
 * @file JumpTest.cpp
 * @author ryanl
 */

#include <pch.h>
#include <memory>
#include <Game.h>
#include <ItemSpartyGnome.h>

#include "gtest/gtest.h"

TEST(JumpTest,Jump)
{
    Game game;
    std::shared_ptr<ItemSpartyGnome> gnome = game.GetGnome();

    gnome->Jump();
    ASSERT_TRUE(gnome->GravityCheck());
    gnome->DisableGravity();
    ASSERT_FALSE(gnome->GravityCheck());
    gnome->Jump();
    ASSERT_TRUE(gnome->GravityCheck());

}

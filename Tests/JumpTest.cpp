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
    ASSERT_TRUE(gnome->IsGravity());
    gnome->DisableGravity();
    ASSERT_FALSE(gnome->IsGravity());
    gnome->Jump();
    ASSERT_TRUE(gnome->IsGravity());

}

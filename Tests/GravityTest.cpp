/**
 * @file GravityTest.cpp
 * @author ryanl
 */

#include <pch.h>
#include <memory>
#include <Game.h>
#include <ItemSpartyGnome.h>

#include "gtest/gtest.h"

TEST(GravityTest,Gravity)
{
    Game* game = new Game();
    ItemSpartyGnome gnome(game);

    gnome.EnableGravity();
    ASSERT_TRUE(gnome.GravityCheck());
    gnome.DisableGravity();
    ASSERT_FALSE(gnome.GravityCheck());
    gnome.EnableGravity();
    ASSERT_TRUE(gnome.GravityCheck());

}

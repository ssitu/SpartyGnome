/**
 * @file BackgroundImage.cpp
 * 
 * @author Simon Situ
 */

#include "pch.h"
#include <string>
#include "BackgroundImage.h"
using namespace std;
const wstring BackGroundImageName = L"images/backgroundForest.png";

BackgroundImage::BackgroundImage(Game* game) : Item(game, BackGroundImageName)
{

}
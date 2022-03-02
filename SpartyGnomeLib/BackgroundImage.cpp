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

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* BackgroundImage::XmlSave(wxXmlNode* node)
{
    auto itemNode = BackgroundImage::XmlSave(node);
    itemNode->AddAttribute(L"type", L"background");

    return itemNode;
}
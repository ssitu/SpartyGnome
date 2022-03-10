/**
 * @file Platform.cpp
 * @author ryanl, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>
#include <wx/graphics.h>

#include "Platform.h"

using namespace std;

const wstring PlatformName = L"images/snow.png";
const wstring ImageDir = L"images/";
const int TileSize = 32;

class Game;

/**
 * Constructor
 * @param game Game this item is a member of
 */
Platform::Platform(Game *game) : Item(game, PlatformName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 */
Platform::Platform(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{
    //Load the left image
    auto image = make_shared<wxImage>(
            ImageDir + declaration->GetAttribute(L"left-image").ToStdWstring(),
            wxBITMAP_TYPE_ANY);
    SetBitmap(make_shared<wxBitmap>(*image));

    //Load the middle image
    mMidImage = make_shared<wxImage>(
            ImageDir + declaration->GetAttribute(L"mid-image").ToStdWstring(),
            wxBITMAP_TYPE_ANY);
    mMidBitmap = make_shared<wxBitmap>(*mMidImage);

    //Load the right image
    mRightImage = make_shared<wxImage>(
            ImageDir + declaration->GetAttribute(L"right-image").ToStdWstring(),
            wxBITMAP_TYPE_ANY);
    mRightBitmap = make_shared<wxBitmap>(*mRightImage);
}

/**
 * Save this platform to an XML node
 * @param node The parent node we are going to be a child of
 * @return The node we are doing to add to the parent.
 */
wxXmlNode* Platform::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    // TODO add support to save each image file of platform
    itemNode->AddAttribute(L"left-image", L"snowLeft.png");
    itemNode->AddAttribute(L"mid-image", L"snowMid.png");
    itemNode->AddAttribute(L"right-image", L"snowRight.png");
    itemNode->AddAttribute(L"type", L"platform");
    return itemNode;
}

/**
 * Draws this platform to the given graphics context
 * @param gc The graphics context
 */
void Platform::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    int leftStart = Item::GetX()-(Item::GetWidth()/2);
    int height = Item::GetY()-(Item::GetHeight()/2);
    //Draw the left tile
    gc->DrawBitmap(*Item::GetBitmap(),
        leftStart,
        height,
        TileSize+1,
        Item::GetHeight());

    // If only one tile needed then return here
    if (Item::GetWidth() <= 32) {
        return;
    }

    // While we are more than 32 pixels away from the right edge of the item...
    for (int i=TileSize; i<=(Item::GetWidth()-(TileSize)); i += TileSize) {
        // Draw a middle tile, then move 32 pixels to the right
        gc->DrawBitmap(*mMidBitmap,
                leftStart + i,
                height,
                TileSize + 1,
                Item::GetHeight());
    }
    // Draw the final tile as a right tile and end the drawing process.
    gc->DrawBitmap(*mRightBitmap,
            Item::GetX()+(Item::GetWidth()/2)-TileSize,
            height,
            TileSize + 1,
            Item::GetHeight());

}



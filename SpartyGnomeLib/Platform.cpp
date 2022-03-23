/**
 * @file Platform.cpp
 * @author ryanl, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>
#include <wx/graphics.h>

#include "Platform.h"
#include "Game.h"

using namespace std;

/// Default image filepath
const wstring PlatformName = L"snow.png";
/// Size of individual platform image tiles
const int TileSize = 32;

class Game;

/**
 * Testing Constructor
 * @param game Game this item is a member of
 */
Platform::Platform(Game* game)
        :Item(game, PlatformName)
{
}

/**
 * The constructor used to load from XML
 * @param declaration The declaration of this item
 * @param item The XML node holding item information
 * @param game The Game that this item is apart of
 */
Platform::Platform(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
        :Item(declaration, item, game)
{
    //Load the left image
    SetPath(declaration->GetAttribute(L"left-image").ToStdWstring());
    SetBitmap(GetGame()->GetBitmap(GetPath()));

    //Load the middle image
    mMidPath = declaration->GetAttribute(L"mid-image").ToStdWstring();
    mMidBitmap = GetGame()->GetBitmap(mMidPath);

    //Load the right image
    mRightPath = declaration->GetAttribute(L"right-image").ToStdWstring();
    mRightBitmap = GetGame()->GetBitmap(mRightPath);
}

/**
 * this is a constructor strictly for testing purposes
 *
 * @author Gabriel Misajlovski
 *
 * @param game game item the platform is in
 * @param leftImageFilename left image
 * @param midImageFilename mid image
 * @param rightImageFilename right image
 */

Platform::Platform(Game* game, const std::wstring& leftImageFilename, const std::wstring& midImageFilename,
        const std::wstring& rightImageFilename)
        :Item(game, leftImageFilename, midImageFilename, rightImageFilename)
{
    //Load the left image
    SetPath(leftImageFilename);
    SetBitmap(GetGame()->GetBitmap(GetPath()));


    //Load the middle image
    mMidPath = midImageFilename;
    mMidBitmap = GetGame()->GetBitmap(mMidPath);


    //Load the right image
    mRightPath = rightImageFilename;
    mRightBitmap = GetGame()->GetBitmap(mRightPath);
}

/**
 * Save this platform to an XML node
 * @param node1 The items parent node we are going to be a child of
 * @param node2 The declarations parent node we are going to be a child of
 * @return 1-2 nodes that were added to the XML file
 */
std::pair<wxXmlNode*,wxXmlNode*> Platform::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    // Pull nodes from Item::XmlSave
    auto doubleNode = Item::XmlSave(node1, node2);
    auto itemNode = doubleNode.first;
    auto declarationNode = doubleNode.second;

    // Edit itemNode attributes
    itemNode->SetName(L"platform");

    // if the declarationNode is not already in declarations
    if (declarationNode != nullptr)
    {
        // Create the declaration (platform takes 3 images in its declaration)
        declarationNode->SetName(L"platform");
        declarationNode->AddAttribute(L"left-image", declarationNode->GetAttribute("image").ToStdWstring());
        declarationNode->DeleteAttribute("image");
        declarationNode->AddAttribute(L"mid-image", mMidPath);
        declarationNode->AddAttribute(L"right-image", mRightPath);
        // return both nodes added
        return make_pair(itemNode, declarationNode);
    }

    // Delete the image attribute from itemNode because itemNode no longer needs it
    itemNode->DeleteAttribute("image");

    // Return just the itemNode
    return make_pair(itemNode, nullptr);
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
    if (Item::GetWidth() <= 32)
    {
        return;
    }

    // While we are more than 32 pixels away from the right edge of the item...
    for (int i = TileSize; i<=(Item::GetWidth()-(TileSize)); i += TileSize)
    {
        // Draw a middle tile, then move 32 pixels to the right
        gc->DrawBitmap(*mMidBitmap,
                leftStart+i,
                height,
                TileSize+1,
                Item::GetHeight());
    }
    // Draw the final tile as a right tile and end the drawing process.
    gc->DrawBitmap(*mRightBitmap,
            Item::GetX()+(Item::GetWidth()/2)-TileSize,
            height,
            TileSize+1,
            Item::GetHeight());

}


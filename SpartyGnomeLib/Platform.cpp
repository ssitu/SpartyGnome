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
 */
Platform::Platform(const wxXmlNode* declaration, const wxXmlNode* item)
        :Item(declaration, item)
{
    //Load the left image
    auto image = make_shared<wxImage>(
            ImageDir+declaration->GetAttribute(L"left-image").ToStdWstring(),
            wxBITMAP_TYPE_ANY);
    SetBitmap(make_shared<wxBitmap>(*image));

    // Save the file path for saving into an xml.
    mMidPath = declaration->GetAttribute(L"mid-image").ToStdWstring();

    //Load the middle image
    mMidImage = make_shared<wxImage>(
            ImageDir+mMidPath,
            wxBITMAP_TYPE_ANY);
    mMidBitmap = make_shared<wxBitmap>(*mMidImage);

    mRightPath = declaration->GetAttribute(L"right-image").ToStdWstring();

    //Load the right image
    mRightImage = make_shared<wxImage>(
            ImageDir+mRightPath,
            wxBITMAP_TYPE_ANY);
    mRightBitmap = make_shared<wxBitmap>(*mRightImage);
}

/**
 * this is a constructor strictly for testing purposes
 *
 * @author Gabriel Misajlovski
 *
 * @param game game item the platform is in
 * @param filename left image
 * @param filename2 mid image
 * @param filename3 right image
 */

Platform::Platform(Game* game, const std::wstring& filename, const std::wstring& filename2,
        const std::wstring& filename3)
        :Item(game, filename, filename2, filename3)
{
    //Load the left image
    auto image = make_shared<wxImage>(
            GetPath(this->GetImage()),
            wxBITMAP_TYPE_ANY);
    SetBitmap(make_shared<wxBitmap>(*image));

    mMidPath = filename2;

    //Load the middle image
    mMidImage = make_shared<wxImage>(
            ImageDir + mMidPath,
            wxBITMAP_TYPE_ANY);
    mMidBitmap = make_shared<wxBitmap>(*mMidImage);

    mRightPath = filename3;

    //Load the right image
    mRightImage = make_shared<wxImage>(
            ImageDir + mRightPath,
            wxBITMAP_TYPE_ANY);
    mRightBitmap = make_shared<wxBitmap>(*mRightImage);
}

/**
 * Save this platform to an XML node
 * @param node The parent node we are going to be a child of
 * @return The node we are doing to add to the parent.
 */
std::pair<wxXmlNode*,wxXmlNode*> Platform::XmlSave(wxXmlNode* node1, wxXmlNode* node2)
{
    auto itemNode = Item::XmlSave(node1, node2).first;
    auto declarationNode = Item::XmlSave(node1, node2).second;
    itemNode->SetName(L"platform");
    declarationNode->SetName(L"platform");

    declarationNode->AddAttribute(L"left-image", itemNode->GetAttribute("image").ToStdWstring());
    itemNode->DeleteAttribute("image");

    declarationNode->AddAttribute(L"mid-image", mMidPath);
    declarationNode->AddAttribute(L"right-image", mRightPath);

    return make_pair(itemNode, declarationNode);
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
    if (Item::GetWidth()<=32) {
        return;
    }

    // While we are more than 32 pixels away from the right edge of the item...
    for (int i = TileSize; i<=(Item::GetWidth()-(TileSize)); i += TileSize) {
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


/**
 * @file Item.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/graphics.h>

#include "Item.h"
#include "Game.h"

using namespace std;

const wstring ImageDir = L"images/";

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game, const wstring &filename) : mGame(game)
{
    mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_shared<wxBitmap>(*mItemImage);
}

/**
 * Draw this item
 * @param gc Graphics context to draw on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> gc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    gc->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2),
            wid + 1,
            hit);
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"id", mId);

    itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mY));
    itemNode->AddAttribute(L"width", wxString::FromDouble(mWidth));
    itemNode->AddAttribute(L"height", wxString::FromDouble(mHeight));

    return itemNode;
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * The constructor to create an item from loading an XML file
 * @param declaration The item tag in the declaration section
 * @param item TThe item tag in the item section
 */
Item::Item(const wxXmlNode* declaration, const wxXmlNode* item)
{
    // Example format:
    // declaration: <background id="i001" image="backgroundForest.png"/>
    // item: <background id="i001" x="512" y="512"/>
    // Get image path

    auto imageAttribute = declaration->GetAttribute(L"image");
    if (imageAttribute != wxEmptyString)
    {
        //TODO: image loading should not be here to avoid loading an image more than once
        auto imagePath = ImageDir + imageAttribute.ToStdWstring();
        auto image = make_shared<wxImage>(imagePath, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_shared<wxBitmap>(*image);
    }

    // Loading generic item information
    item->GetAttribute(L"x").ToDouble(&mX);
    item->GetAttribute(L"y").ToDouble(&mY);
    item->GetAttribute(L"width").ToDouble(&mWidth);
    item->GetAttribute(L"height").ToDouble(&mHeight);
    mId = declaration->GetAttribute(L"id").ToStdWstring();
    mType = item->GetName();


}
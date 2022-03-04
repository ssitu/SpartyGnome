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
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}

/**
 * Draw this item
 * @param gc Graphics context to draw on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> gc)
{

    if(mItemBitmap->IsNull())

    mItemBitmap = make_shared<wxBitmap>(*mItemImage);

    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    gc->PushState();
    gc->Translate(0, 0);

    gc->DrawBitmap(*mItemBitmap,
            int(GetX()- wid / 2),
            int(GetY()- hit / 2),
            wid + 1,
            hit);
    gc->PopState();
//    );

//    double wid = mItemBitmap->GetWidth();
//    double hit = mItemBitmap->GetHeight();
//    gc->DrawBitmap(*mItemBitmap,
//            int(GetX() - wid / 2),
//            int(GetY() - hit / 2),
//            wid + 1,
//            hit
//            );
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
 * @param declaration The declaration of the item
 * @param item The item specifications
 */
Item::Item(const wxXmlNode* declaration, const wxXmlNode* item)
{
    wstring imageFileName;
    // Example format:
    // declaration: <background id="i001" image="backgroundForest.png"/>
    // item: <background id="i001" x="512" y="512"/>
    // Get image path
    if (item->GetName()!=L"platform") {
        imageFileName = declaration->GetAttribute(L"image").ToStdWstring();
    }
    else {
        double width = item->GetAttribute(L"width", L"32").ToDouble(&width);
        double tiles = width/32;

        if (tiles==1) {
            imageFileName = declaration->GetAttribute(L"mid-image", L"snow.png").ToStdWstring();
        }
        else if (tiles==2) {
            imageFileName = declaration->GetAttribute(L"left-image").ToStdWstring();
        } else {
            imageFileName = declaration->GetAttribute(L"mid-image", L"snow.png").ToStdWstring();
        }
        shared_ptr<Platform> platform;
        double x = item->GetAttribute(L"x", "0").ToDouble(&x);
        double y = item->GetAttribute(L"y", "0").ToDouble(&y);
        // mGame->Add(platform, x+width, y);
    }

        // Creating and storing the image and bitmap
        mItemImage = make_unique<wxImage>(ImageDir+imageFileName, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_unique<wxBitmap>(*mItemImage);

        // Item location
        item->GetAttribute(L"x").ToDouble(&mX);
        item->GetAttribute(L"y").ToDouble(&mY);


}
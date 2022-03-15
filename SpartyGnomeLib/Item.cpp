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
    mPath = filename;
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
 * @return pair of wxXmlNodes that we saved the item and declaration into
 */
pair<wxXmlNode*, wxXmlNode*>Item::XmlSave(wxXmlNode *node1, wxXmlNode *node2)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    auto declarationNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"declaration");
    bool hasId = false;
    node1->AddChild(itemNode);

    itemNode->AddAttribute(L"id", mId);
    itemNode->AddAttribute(L"x", wxString::FromDouble(mInitialX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mInitialY));
    itemNode->AddAttribute(L"width", wxString::FromDouble(mWidth));
    itemNode->AddAttribute(L"height", wxString::FromDouble(mHeight));


    if (node2->GetChildren() == nullptr) {
        node2->AddChild(declarationNode);
        declarationNode->AddAttribute(L"id", mId);
        declarationNode->AddAttribute("image", mPath);
        return make_pair(itemNode, declarationNode);
    } else {
        for (auto node = node2->GetChildren(); node; node = node->GetNext()) {
            if (node->GetAttribute(L"id")==mId) {
                hasId = true;
            }
        }
        if (!hasId) {
            node2->AddChild(declarationNode);
            declarationNode->AddAttribute(L"id", mId);
            declarationNode->AddAttribute("image", mPath);
            return make_pair(itemNode, declarationNode);
        }
    }

    return make_pair(itemNode, nullptr);
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + mWidth / 2;
    double testY = y - GetY() + mHeight / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= mWidth || testY >= mHeight)
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

    auto imageAttribute2 = declaration->GetAttribute(L"left-image");
    if (imageAttribute != wxEmptyString)
    {
        //TODO: image loading should not be here to avoid loading an image more than once
        mPath = imageAttribute.ToStdWstring();
        auto image = make_shared<wxImage>(ImageDir + mPath, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_shared<wxBitmap>(*image);
    } else if (imageAttribute2 != wxEmptyString) {
        mPath = imageAttribute2.ToStdWstring();
        auto image = make_shared<wxImage>(ImageDir + mPath, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_shared<wxBitmap>(*image);
    }

    // Loading generic item information
    item->GetAttribute(L"x").ToDouble(&mX);
    item->GetAttribute(L"y").ToDouble(&mY);
    item->GetAttribute(L"x").ToDouble(&mInitialX);
    item->GetAttribute(L"y").ToDouble(&mInitialY);
    item->GetAttribute(L"width").ToDouble(&mWidth);
    item->GetAttribute(L"height").ToDouble(&mHeight);
    mId = declaration->GetAttribute(L"id").ToStdWstring();


}

/**
 * Tests if a rectangular collision occurred between this item and the given item
 * @param item The other item to test collision with
 * @return True if there is a collision, false otherwise
 */
const bool Item::CollisionTest(Item* item) const
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetWidth() / 2;
    auto itemRight = item->GetX() + item->GetWidth() / 2;
    auto itemTop = item->GetY() - item->GetHeight() / 2;
    auto itemBottom = item->GetY() + item->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two items
    if (ourRight < itemLeft ||  // Completely to the left
            ourLeft > itemRight ||  // Completely to the right
            ourTop > itemBottom ||  // Completely below
            ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}
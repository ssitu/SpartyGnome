/**
 * @file Item.cpp
 * @author Gabriel Misajlovski, ryanl
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
 * @param filename the name of the imagefile for this item
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game)
{
    mPath = filename;
    mItemBitmap = game->GetBitmap(filename);
}

void Item::OnCollision(Item* item){

}
/**
 * Constructor for the item with only the Game pointer
 * @param game The Game this is apart of
 */
Item::Item(Game* game)
{
    mGame = game;
}

/**
 * The constructor to create an item from loading an XML file
 * @param declaration The item tag in the declaration section
 * @param item The item tag in the item section
 * @param game The Game this Item is apart of
 */
Item::Item(const wxXmlNode* declaration, const wxXmlNode* item, Game* game)
{
    mGame = game;
    // Example format:
    // declaration: <background id="i001" image="backgroundForest.png"/>
    // item: <background id="i001" x="512" y="512"/>

    // Get image path
    auto imageAttribute = declaration->GetAttribute(L"image");
    mPath = imageAttribute.ToStdWstring();
    if (imageAttribute != wxEmptyString)
    {
        mItemBitmap = GetGame()->GetBitmap(mPath);
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
    // Create a new item and declaration node
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    auto declarationNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"declaration");

    // Set a check for if the declarations node we are saving to has the id of the image or not.
    bool hasId = false;

    // Add the item node to the items node
    node1->AddChild(itemNode);

    // Set the attributes for this item node
    itemNode->AddAttribute(L"id", mId);
    itemNode->AddAttribute(L"x", wxString::FromDouble(mInitialX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mInitialY));
    itemNode->AddAttribute(L"width", wxString::FromDouble(mWidth));
    itemNode->AddAttribute(L"height", wxString::FromDouble(mHeight));

    // If declarations node does not have any children...
    if (node2->GetChildren() == nullptr) {
        // Add this node as a child
        node2->AddChild(declarationNode);

        // Set this node's attributes
        declarationNode->AddAttribute(L"id", mId);
        declarationNode->AddAttribute("image", mPath);

        // return a pair of the itemNode and declarationNode that were added.
        return make_pair(itemNode, declarationNode);
    }
    // else if it has children...
    else
    {
        // Check to see if the declarations node has a child with this Id already or not...
        for (auto node = node2->GetChildren(); node; node = node->GetNext()) {
            if (node->GetAttribute(L"id")==mId) {
                hasId = true;
            }
        }
        // If the parent does not have a child with the same Id...
        if (!hasId) {
            // Add this node to declarations
            node2->AddChild(declarationNode);

            // Set the attributes
            declarationNode->AddAttribute(L"id", mId);
            declarationNode->AddAttribute("image", mPath);

            // return pair of added itemNode and declarationNode
            return make_pair(itemNode, declarationNode);
        }
    }

    // If the declarationNode already exists in declarations, return
    // just the itemNode with declarationNode as nullptr
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
}

/**
 * Tests if a rectangular collision occurred between this item and the given item
 * @param item The other item to test collision with
 * @return True if there is a collision, false otherwise
 */
bool Item::CollisionTest(Item* item)
{
    // Border for the item
    auto itemLeft = item->GetX()-item->GetWidth()/2;
    auto itemRight = item->GetX()+item->GetWidth()/2;
    auto itemTop = item->GetY()-item->GetHeight()/2;
    auto itemBottom = item->GetY()+item->GetHeight()/2;

    // For us
    auto ourLeft = GetX()-GetWidth()/2;
    auto ourRight = GetX()+GetWidth()/2;
    auto ourTop = GetY()-GetHeight()/2;
    auto ourBottom = GetY()+GetHeight()/2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two items
    if (ourRight<itemLeft ||  // Completely to the left
            ourLeft>itemRight ||  // Completely to the right
            ourTop>itemBottom ||  // Completely below
            ourBottom<itemTop)    // Completely above
    {
        return false;
    }

    return true;
}


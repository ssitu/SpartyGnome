/**
 * @file Platform.cpp
 * @author ryanl, Gabriel Misajlovski
 */

#include "pch.h"

#include <string>

#include "Platform.h"

using namespace std;

const wstring directory = L"images/";
wstring PlatformName = L"images/composite.png";

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

}

/**
 * Save this platform to an XML node
 * @param node The parent node we are going to be a child of
 * @return The node we are doing to add to the parent.
 */
wxXmlNode* Platform::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"width", wxString::FromDouble(GetWidth()));
    itemNode->AddAttribute(L"height", wxString::FromDouble(GetHeight()));
    itemNode->AddAttribute(L"type", L"platform");
    // itemNode->AddAttribute(L"left-image", mLeftImage);
    // itemNode->AddAttribute(L"mid-image", mMidImage);
    // itemNode->AddAttribute(L"right-image", mRightImage);
    return itemNode;
}

/**
 * A currently Failed attempt at trying to turn 3 images into a single
 * bitmap.
 * @param item
 */
void Platform::SaveCompositeImage(wxXmlNode* item)
{
    if ((directory + item->GetAttribute(L"mid-image") != L"images/")
            && (directory + item->GetAttribute(L"left-image") != L"images/")
            && (directory + item->GetAttribute(L"mid-image") != L"images/")) {
        auto midBitmap = make_shared<wxBitmap>(*make_shared<wxImage>(item->GetAttribute(L"mid-image"),
                wxBITMAP_TYPE_ANY), wxBITMAP_TYPE_ANY);
        auto leftBitmap = make_shared<wxBitmap>(*make_shared<wxImage>(item->GetAttribute(L"left-image"),
                wxBITMAP_TYPE_ANY), wxBITMAP_TYPE_ANY);
        auto rightBitmap = make_shared<wxBitmap>(*make_shared<wxImage>(item->GetAttribute(L"right-image"),
                wxBITMAP_TYPE_ANY), wxBITMAP_TYPE_ANY);

        wxBitmap background((midBitmap->GetWidth()*3), midBitmap->GetHeight());
        wxMemoryDC mdc(background);

        auto midImage = make_shared<wxImage>(item->GetAttribute(L"mid-image"), wxBITMAP_TYPE_ANY);
        auto width = midImage->GetWidth();

        mdc.DrawBitmap(background, 0, 0);
        mdc.DrawBitmap(*leftBitmap, 0, 0);
        mdc.DrawBitmap(*midBitmap, width, 0);
        mdc.DrawBitmap(*rightBitmap, width*2, 0);

        background.SaveFile("images/composite.png", wxBITMAP_TYPE_PNG);


    }
}


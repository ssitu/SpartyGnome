/**
 * @file SpartyGnomeView.cpp
 * @author ryanl
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "ids.h"
#include "Game.h"
#include "BackgroundImage.h"
#include "ItemSpartyGnome.h"
#include "SpartyGnomeView.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

void SpartyGnomeView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SpartyGnomeView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SpartyGnomeView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &SpartyGnomeView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &SpartyGnomeView::OnMouseMove, this);
    Bind(wxEVT_KEY_DOWN, &SpartyGnomeView::OnKeyDown, this);
    //Bind(wxEVT_KEY_UP, &SpartyGnomeView::OnKeyUp, this);
    //Bind the timer event handler
    Bind(wxEVT_TIMER, &SpartyGnomeView::OnTimer, this);
//    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnAddSpartyGnome, this, IDM_ADDSPARTYGNOME);
//    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnAddPlatform, this, IDM_ADDPLATFORM);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnFileSaveas, this, wxID_SAVEAS);
    parent->Bind(wxEVT_CLOSE_WINDOW, &SpartyGnomeView::OnClose, this, wxID_CLOSE);

    /// This is to make 4 backgrounds, extended by side to side
    for (int i = 0; i<5; i++)
    {
        auto bg = make_shared<BackgroundImage>(&mGame);
        mGame.Add(bg, -1024+1024*i, 512);
    }

    auto spartyGnome = make_shared<ItemSpartyGnome>(&mGame);
    mGame.AddGnome(spartyGnome);

    auto platform = make_shared<Platform>(&mGame);
    mGame.Add(platform, 512, 512 + (mGame.GetGnome()->GetHeight() / 2) + (platform->GetHeight() / 2));

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

    mParent = parent;
}

//void SpartyGnomeView::OnAddSpartyGnome(wxCommandEvent& event)
//{
//    auto gnome = make_shared<ItemSpartyGnome>(&mGame);
//    mGame.AddGnome(gnome);
//}

// void SpartyGnomeView::OnAddPlatform(double x, double y)
// {
//     auto platform = make_shared<Platform>(&mGame);
//     mGame.Add(platform, x, y);
// }

/**
 *
 * @param event
 */
void SpartyGnomeView::OnPaint(wxPaintEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);

    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
}

/**
 * OnTimer event handler
 * @param event The wx event
 */
void SpartyGnomeView::OnTimer(wxTimerEvent& event) { Refresh(); }


/**
 * Handle the left mouse button down event
 * @param event
 */
void SpartyGnomeView::OnLeftDown(wxMouseEvent &event)
{
//    mGrabbedItem = mGame.HitTest(event.GetX(), event.GetY());
//    if (mGrabbedItem != nullptr)
//    {
//        // We have selected an item
//        // Move it to the end of the list of items
//        // you'll need code here to do that...
//        mGame.NewOrder(mGrabbedItem);
//    }
}

/**
* Handle the left mouse button down event
* @param event
*/
void SpartyGnomeView::OnLeftUp(wxMouseEvent &event)
{
//    OnMouseMove(event);
}

/**
* Handle the left mouse button down event
* @param event
*/
void SpartyGnomeView::OnMouseMove(wxMouseEvent &event)
{
//    // See if an item is currently being moved by the mouse
//    if (mGrabbedItem != nullptr)
//    {
//        // If an item is being moved, we only continue to
//        // move it while the left button is down.
//        if (event.LeftIsDown())
//        {
//            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
//        }
//        else
//        {
//            // When the left button is released, we release the
//            // item.
//            mGrabbedItem = nullptr;
//        }
//
//        // Force the screen to redraw
//        Refresh();
//    }
}


void SpartyGnomeView::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
        // right arrow pressed
        break;

    case WXK_LEFT:
        // left arrow pressed
        break;

    case WXK_SPACE:
        // space bar pressed
        mGame.GetGnome()->Jump();
        break;
    }
}

void SpartyGnomeView::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
    case WXK_LEFT:
        // left or right arrow released
        break;
    }
}

/**
 * Saves the file containing the game and its objects.
 * @param event
 */
void SpartyGnomeView::OnFileSaveas(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Level file"), "", "",
            "Game Files (*.xml)|*.xml", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mGame.Save(filename);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void SpartyGnomeView::OnClose(wxCloseEvent& event)
{
    this->Stop();
    Destroy();
}

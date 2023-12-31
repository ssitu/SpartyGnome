/**
 * @file SpartyGnomeView.cpp
 * @author ryanl, Gabriel Misajlovski
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/file.h>

#include "Game.h"
#include "SpartyGnomeView.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;
/// Max elapsed frame delay
const double MaxElapsed = .050;

/**
 * Creation of the window
 * @param parent the MainFrame
 */
void SpartyGnomeView::Initialize(wxFrame* parent)
{
    // create a value to hold the parent and set background for window
    Create(parent, wxID_ANY);
    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // New Bindings to default wx Event Handlers
    Bind(wxEVT_PAINT, &SpartyGnomeView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &SpartyGnomeView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &SpartyGnomeView::OnKeyUp, this);
    Bind(wxEVT_TIMER, &SpartyGnomeView::OnTimer, this);

    // Binding Save and Load functions.
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnFileSaveas, this, wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnFileOpen, this, wxID_OPEN);

    // Bindings for level loading menu
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnLevelOpen, this, wxID_FILE1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnLevelOpen, this, wxID_FILE2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnLevelOpen, this, wxID_FILE3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyGnomeView::OnLevelOpen, this, wxID_FILE4);

    // Start the timer for updates
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

    // Set member variable mPrent
    mParent = parent;

    // Load the default level on startup
    mGame.LevelLoadDefault();
}

/**
 * New handler for paint event
 * @param event wxEVT_PAINT
 */
void SpartyGnomeView::OnPaint(wxPaintEvent& event)
{
    // pull a new time from Timer
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Update the game
    // Prevent tunnelling
    while (elapsed > MaxElapsed)
    {
        mGame.Update(MaxElapsed);
        elapsed -= MaxElapsed;
    }

    // Consume any remaining time
    if (elapsed > 0)
    {
        mGame.Update(elapsed);
    }

    // crate a wxDCBuffer
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // create a graphics context from the DCBuffer
    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
}

/**
 * OnTimer event handler
 * @param event wxEVT_TIMER
 */
void SpartyGnomeView::OnTimer(wxTimerEvent& event) { Refresh(); }

/**
 * Handler for key down event
 * @param event wxEVT_KEY_DOWN
 */
void SpartyGnomeView::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
    case 'D':
        // right arrow pressed
        mGame.GetGnome()->MoveRight();
        break;

    case WXK_LEFT:
    case 'A':
        // left arrow pressed
        mGame.GetGnome()->MoveLeft();
        break;

    case WXK_SPACE:
        // space bar pressed
        mGame.GetGnome()->Jump();
        break;

    }
}

/**
 * Handler for key up event
 * @param event wxEVT_KEY_UP
 */
void SpartyGnomeView::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_RIGHT:
    case 'D':
        mGame.GetGnome()->StopMove();
        break;
    case WXK_LEFT:
    case 'A':
        // left or right arrow released
        mGame.GetGnome()->StopMove();
        break;
    }
}

/**
 * Saves the file containing the game and its objects.
 * @param event Saving a file
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
 * Loads a chosen XML file
 * @param event loading a file
 */
void SpartyGnomeView::OnFileOpen(wxCommandEvent& event)
{
    mGame.GetGnome()->DisableGravity();
    wxFileDialog loadFileDialog(this, _("Load Level file"), "levels", "",
            "", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mGame.LevelLoad(filename.ToStdWstring());
}

/**
 * The level loading menu
 * @param event clicking on a level to load
 */
void SpartyGnomeView::OnLevelOpen(wxCommandEvent& event)
{
    switch (event.GetId()) {
    case wxID_FILE1:
        mGame.LevelLoad(0);
        break;
    case wxID_FILE2:
        mGame.LevelLoad(1);
        break;
    case wxID_FILE3:
        mGame.LevelLoad(2);
        break;
    case wxID_FILE4:
        mGame.LevelLoad(3);
        break;

    }
}

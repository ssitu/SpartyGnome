/**
 * @file SpartyGnomeView.cpp
 * @author ryanl
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "ids.h"
#include "Game.h"
#include "SpartyGnomeView.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Game area height in virtual pixels
const static int Height = 1024;

void SpartyGnomeView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SpartyGnomeView::OnPaint, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}

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
    mGame.OnDraw(graphics, size->GetWidth(), size->GetHeight());
}

void SpartyGnomeView::OnTimer(wxTimerEvent& event) { Refresh(); }


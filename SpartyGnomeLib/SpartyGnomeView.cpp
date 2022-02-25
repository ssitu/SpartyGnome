/**
 * @file SpartyGnomeView.cpp
 * @author ryanl
 */

#include "pch.h"
#include "SpartyGnomeView.h"

void SpartyGnomeView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY);

    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

}

void SpartyGnomeView::Update()
{
    //Refresh Function
}

void SpartyGnomeView::OnPaint(wxPaintEvent& parent)
{
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
}
/**
 * @file SpartyGnomeView.cpp
 * @author ryanl
 */

#include "pch.h"
#include "SpartyGnomeView.h"

void SpartyGnomeView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

}
/**
 * @file MainFrame.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartyGnomeView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"SpartyGnome",wxDefaultPosition,  wxSize( 1000,800 ));

    auto spartygnomeview = new SpartyGnomeView();
    spartygnomeview->Initialize(this);

}

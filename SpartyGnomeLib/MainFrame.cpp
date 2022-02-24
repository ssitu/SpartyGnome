/**
 * @file MainFrame.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"
#include "MainFrame.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty Gnome",
            wxDefaultPosition,  wxSize( 1000,800 ));

}
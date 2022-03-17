/**
 * @file SpartyGnomeApp.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartyGnomeApp.h"

/**
 * Initialize the application.
 * @return bool Whether it was initialized successfully or not
 */
bool SpartyGnomeApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}

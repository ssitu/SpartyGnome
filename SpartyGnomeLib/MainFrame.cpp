/**
 * @file MainFrame.cpp
 * @author Gabriel Misajlovski, ryanl
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartyGnomeView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    // Create the window container
    Create(nullptr, wxID_ANY, L"Sparty Gnome",wxDefaultPosition,  wxSize( 1000,800 ));

    // Create the window
    mGameView = new SpartyGnomeView();
    mGameView->Initialize(this);

    // Add menubar
    auto menuBar = new wxMenuBar();

    // Create menus
    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // itemMenu for testing and level creation purposes only
    auto itemMenu = new wxMenu();

    // Add options to menuBar
    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"Levels");
    menuBar->Append(helpMenu, L"&Help");
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");

    // These two are for level creation and testing purposes only
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save game as...");
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open xml level file...");

    // Add options to levelMenu
    levelMenu->Append(wxID_FILE1, L"Level &0");
    levelMenu->Append(wxID_FILE2, L"Level &1");
    levelMenu->Append(wxID_FILE3, L"Level &2");
    levelMenu->Append(wxID_FILE4, L"Level &3");

    // Add helpMenu option
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    // Set the menuBar
    SetMenuBar(menuBar);

    // Creating a Status Bar
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    // Bind MainFrame event handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
}

/**
 * Exit menu option handlers
 * @param event The wx event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}

/**
 * About menu option handler
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Sparty Gnome",
            L"About Sparty Gnome",
            wxOK,
            this);
}
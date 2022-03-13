/**
 * @file MainFrame.cpp
 * @author Gabriel Misajlovski
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartyGnomeView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty Gnome",wxDefaultPosition,  wxSize( 1000,800 ));

    mGameView = new SpartyGnomeView();
    mGameView->Initialize(this);

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // itemMenu for testing and level creation purposes only
    auto itemMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"Levels");
    menuBar->Append(itemMenu, L"&Add Item");
    menuBar->Append(helpMenu, L"&Help");
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");

    // These two are for level creation and testing purposes only
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save game as...");
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open xml level file...");

    levelMenu->Append(wxID_FILE1, L"Level &0");
    levelMenu->Append(wxID_FILE2, L"Level &1");
    levelMenu->Append(wxID_FILE3, L"Level &2");
    levelMenu->Append(wxID_FILE4, L"Level &3");

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    itemMenu->Append(IDM_ADDSPARTYGNOME, L"&Sparty Gnome", L"Add a Sparty Gnome");
    itemMenu->Append(IDM_ADDPLATFORM, L"&Platform", L"Add a Platform");

    SetMenuBar( menuBar );

    // Creating a Status Bar
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );


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
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Sparty Gnome",
            L"About Sparty Gnome",
            wxOK,
            this);

}
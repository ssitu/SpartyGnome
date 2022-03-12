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
    auto helpMenu = new wxMenu();
    auto itemMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(itemMenu, L"&Add Item");
    menuBar->Append(helpMenu, L"&Help");
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save game as...");
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open xml level file...");

    itemMenu->Append(IDM_ADDSPARTYGNOME, L"&Sparty Gnome", L"Add a Sparty Gnome");
    itemMenu->Append(IDM_ADDPLATFORM, L"&Platform", L"Add a Platform");

    SetMenuBar( menuBar );

    // Creating a Status Bar
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );


    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
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
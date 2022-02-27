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
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
    Create(nullptr, wxID_ANY, L"Sparty Gnome",wxDefaultPosition,  wxSize( 1000,800 ));

    auto spartygnomeview = new SpartyGnomeView();
    spartygnomeview->Initialize(this);

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto itemMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(itemMenu, L"&Add Item");
    menuBar->Append(helpMenu, L"&Help");

    itemMenu->Append(IDM_ADDSPARTYGNOME, L"&Sparty Gnome", L"Add a Sparty Gnome");

    SetMenuBar( menuBar );

    wxMessageBox(L"Welcome to Sparty Gnome!",
            L"About Sparty Gnome",
            wxOK,
            this);



}

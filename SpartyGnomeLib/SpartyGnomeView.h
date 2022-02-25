/**
 * @file SpartyGnomeView.h
 * @author ryanl
 *
 *
 */

#ifndef SPARTYGNOME_SPARTYGNOMEVIEW_H
#define SPARTYGNOME_SPARTYGNOMEVIEW_H

#include "Game.h"

class SpartyGnomeView : public wxWindow {
private:
    Game mGame;
public:
    void Initialize(wxFrame *mainFrame);
    void AddMenus(wxFrame* mainFrame, wxMenuBar* menuBar, wxMenu* fileMenu, wxMenu* viewMenu);

};

#endif //SPARTYGNOME_SPARTYGNOMEVIEW_H

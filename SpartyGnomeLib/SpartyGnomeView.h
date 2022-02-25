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

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    void OnPaint(wxPaintEvent& parent);

public:
    void Initialize(wxFrame *mainFrame);
    void AddMenus(wxFrame* mainFrame, wxMenuBar* menuBar, wxMenu* fileMenu, wxMenu* viewMenu);
    void Update();

};

#endif //SPARTYGNOME_SPARTYGNOMEVIEW_H

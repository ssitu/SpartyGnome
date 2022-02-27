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
    void OnPaint(wxPaintEvent& event);

    void OnTimer(wxTimerEvent &event);

    /// An object that describes our game
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    int mHeight = 800;
    int mWidth = 1000;

public:
    void Initialize(wxFrame* parent);
    void OnAddSpartyGnome(wxCommandEvent& event);
    SpartyGnomeView* GetClientSize() { return this; };

    int GetHeight() { return mHeight; }

    int GetWidth() { return mWidth; }





};

#endif //SPARTYGNOME_SPARTYGNOMEVIEW_H

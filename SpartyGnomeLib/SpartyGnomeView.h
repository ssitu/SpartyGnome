/**
 * @file SpartyGnomeView.h
 * @author ryanl
 *
 *
 */

#ifndef PROJECT1_SPARTYGNOMEVIEW_H
#define PROJECT1_SPARTYGNOMEVIEW_H

#include "Game.h"

class SpartyGnomeView : public wxWindow {
public:
    void Initialize(wxFrame* parent);
    SpartyGnomeView* GetClientSize() { return this; };

    int GetHeight() { return mHeight; }

    int GetWidth() { return mWidth; }

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

    int mHeight = this->GetHeight();
    int mWidth = this->GetWidth();



};

#endif //PROJECT1_SPARTYGNOMEVIEW_H

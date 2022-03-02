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

    /// The pointer to the parent frame
    wxFrame* mParent;

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

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

public:
    void Initialize(wxFrame* parent);
    // void OnAddSpartyGnome(wxCommandEvent& event);
    // void OnAddPlatform(wxCommandEvent& event);

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);

    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);
    /**
     * Obtains the size of the window
     * @return A wxSize object representing the size of the window
     */
    wxSize GetClientSize() { return mParent->GetClientSize(); };





};

#endif //SPARTYGNOME_SPARTYGNOMEVIEW_H

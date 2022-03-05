/**
 * @file MainFrame.h
 * @author Gabriel Misajlovski
 *
 * Declaration of MainFrame
 */

#ifndef SPARTYGNOME_MAINFRAME_H
#define SPARTYGNOME_MAINFRAME_H

class SpartyGnomeView;

/**
* The top-level (main) frame of the application
*/
class MainFrame : public wxFrame {
private:
    /// The pointer to the game view
    SpartyGnomeView* mGameView;

    void OnClose(wxCloseEvent& event);
public:
    void Initialize();

    void OnExit(wxCommandEvent& event);
};

#endif //SPARTYGNOME_MAINFRAME_H

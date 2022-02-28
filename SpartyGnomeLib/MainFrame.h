/**
 * @file MainFrame.h
 * @author Gabriel Misajlovski
 *
 * Declaration of MainFrame
 */

#ifndef SPARTYGNOME_MAINFRAME_H
#define SPARTYGNOME_MAINFRAME_H


/**
* The top-level (main) frame of the application
*/
class MainFrame : public wxFrame {
public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
};

#endif //SPARTYGNOME_MAINFRAME_H

/**
 * @file SpartyGnomeApp.h
 * @author Gabriel Misajlovski
 *
 * Declaration of SpartyGnomeApp Class
 */

#ifndef SPARTYGNOME_SPARTYGNOMEAPP_H
#define SPARTYGNOME_SPARTYGNOMEAPP_H

#include <wx/wx.h>

/**
 * The application class for SpartyGnome game
 */
class SpartyGnomeApp : public wxApp {
public:
    virtual bool OnInit() override;

};

#endif //SPARTYGNOME_SPARTYGNOMEAPP_H

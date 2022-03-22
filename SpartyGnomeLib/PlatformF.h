/**
 * @file PlatformF.h
 * @author Gabriel Misajlovski
 *
 * Platform F class. (a.k.a. Disappearing Platform Class)
 */

#ifndef SPARTYGNOME_PLATFORMF_H
#define SPARTYGNOME_PLATFORMF_H

#include "Platform.h"

/**
 * The Platform F class
 */
class PlatformF : public Platform {
private:
    /// The duration in seconds to keep this platform alive for after being collided with
    double mDuration;
    /// Indicates if this has been collided with, used to start counting down on the duration
    bool mLandedUpon = false;
public:
    /// Default constructor (disabled)
    PlatformF() = delete;

    /// Copy constructor (disabled)
    PlatformF(const PlatformF &) = delete;

    /// Assignment operator
    void operator=(const PlatformF &) = delete;

    /// New constructors
    PlatformF(Game* game);
    PlatformF(const wxXmlNode* declaration, const wxXmlNode* item, Game* game);

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitPlatformF(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void Update(double elapsed) override;
    void OnCollision(Item* item) override;

};

#endif //SPARTYGNOME_PLATFORMF_H

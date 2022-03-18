/**
 * @file PlatformF.h
 * @author Gabriel Misajlovski
 *
 * Platform F class. (a.k.a. Disappearing Platform Class)
 */

#ifndef SPARTYGNOME_PLATFORMF_H
#define SPARTYGNOME_PLATFORMF_H

#include "Platform.h"

class PlatformF : public Platform {
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
     * Check for if platform is fake or not.
     * @return bool
     */
    bool IsF() override { return true; }

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    void Accept(ItemVisitor* visitor) override {visitor->VisitPlatformF(this);}

    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* node1, wxXmlNode* node2) override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

};

#endif //SPARTYGNOME_PLATFORMF_H

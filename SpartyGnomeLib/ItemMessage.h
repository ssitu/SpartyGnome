/**
 * @file ItemMessage.h
 *
 * @author Simon Situ
 *
 * An item that displays a message on the screen
 */

#ifndef SPARTYGNOME_ITEMMESSAGE_H
#define SPARTYGNOME_ITEMMESSAGE_H

#include "Item.h"

/**
 * The item that will display a message on the screen
 */
class ItemMessage : public Item {
private:
    /// The time to display the message for in seconds
    double mDuration;

    /// The message to display when drawn
    std::wstring mMessage;

    /// The pointer to the Game this message is apart of
    Game* mGame;

protected:
    /**
     * Setter for the message to display
     * @param message The new message to use
     */
    void SetMessage(std::wstring message) {mMessage = message;}

public:
    /// disabled default constructor
    ItemMessage() = delete;

    /// disabled copy
    ItemMessage(const ItemDoor&) = delete;

    /// disabled assignment
    void operator=(const ItemMessage&) = delete;

    ItemMessage(Game* game, const std::wstring& message, double duration);

    /**
     * Messages aren't saved, empty function
     * @param items The items node
     * @param declarations The declarations node
     * @return A pair of nulls
     */
    std::pair<wxXmlNode*,wxXmlNode*> XmlSave(wxXmlNode* items, wxXmlNode* declarations) override
        { return std::pair(nullptr, nullptr); }

    /**
     * Accept a visitor
     * @param visitor Visitor to accept
     */
    virtual void Accept(ItemVisitor* visitor) override {visitor->VisitMessage(this);}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    virtual void Update(double elapsed) override;

};

#endif //SPARTYGNOME_ITEMMESSAGE_H

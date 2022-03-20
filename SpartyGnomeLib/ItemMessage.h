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
#include "Vector.h"

/**
 * The item that will display a message on the screen
 */
class ItemMessage : public Item {
private:
    /// The time to display the message for in seconds
    double mDuration;

    /// Boolean to pause the duration
    bool mPauseDuration = false;

    /// The message to display when drawn
    std::wstring mMessage;

    /// The color of the message to display
    wxColour mColor;

    /// The font of the message to display
    wxFont mFont;

    /// The font pixel width
    double mFontPixelWidth;

    /// The font pixel height;
    double mFontPixelHeight;

protected:
    /**
     * Getter for the displayed message
     * @return The displayed
     */
    std::wstring GetMessage() {return mMessage;}

    /**
     * Setter for the message to display
     * @param message The new message to use
     */
    void SetMessage(std::wstring message) {mMessage = message;}

    void SetFontSize(double pixelWidth, double pixelHeight);
    double GetFontWidth();
    double GetFontHeight();

    /**
     * Pause or unpause the duration of the message
     * @param pause True to pause, false to unpause
     */
    void PauseDuration(bool pause) { mPauseDuration = pause; }



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

    /**
     * Setter for the text RGB color
     * @param red Red value
     * @param green Green value
     * @param blue Blue value
     */
    void SetColor(int red, int green, int blue) {mColor = wxColour(red, green, blue); }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    virtual void Update(double elapsed) override;

};

#endif //SPARTYGNOME_ITEMMESSAGE_H

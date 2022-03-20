/**
 * @file ItemMessageAnimated.h
 * 
 * @author Simon Situ
 *
 * The class for animated messages
 */

#ifndef SPARTYGNOME_ITEMMESSAGEANIMATED_H
#define SPARTYGNOME_ITEMMESSAGEANIMATED_H

#include "ItemMessage.h"
#include "Vector.h"

/**
 * The class for animated messages
 */
class ItemMessageAnimated : public ItemMessage {
private:
    /// The velocity of this message in pixels per second
    Vector mVelocity = Vector(0, 0);
    /// The acceleration of this message in pixels per second squared
    Vector mAcceleration = Vector(0, 0);
    /// The size change of this message in pixels per second
    Vector mSizeChange = Vector(0, 0);
public:
    ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
            int fontWidth, int fontHeight);

    ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
            int fontWidth, int fontHeight,
            Vector velocity);

    ItemMessageAnimated(Game* game, const std::wstring& message, double duration,
            int fontWidth, int fontHeight,
            Vector velocity, Vector acceleration);
    void Update(double elapsed) override;
    void SetVelocity(const Vector& v);
    void SetAcceleration(const Vector& a);
    void SetSizeChange(const Vector& s);

};

#endif //SPARTYGNOME_ITEMMESSAGEANIMATED_H

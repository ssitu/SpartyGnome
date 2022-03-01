/**
 * @file Vector.h
 * @author Gabriel Misajlovski
 *
 * Vector Class (Used for movement of objects)
 */

#ifndef SPARTYGNOME_VECTOR_H
#define SPARTYGNOME_VECTOR_H

class Vector {
private:
    double mX;
    double mY;

public:
    /// Default constructor
    Vector() { mX = 0; mY = 0; }

    /// New Constructor
    Vector(double x, double y) { mX = x; mY = y; }

    /// Assignment operator
    Vector operator=(Vector other) { return Vector(other.X(), other.Y()); }

    /// Multiplication operator
    Vector operator*(double z) { return Vector(mX * z, mY * z); }

    /// Addition operator
    Vector operator+(Vector other) { return Vector(mX + other.X(), mY + other.Y()); }

    /// Destructor
    ~Vector();

    /// Setters for x and y coordinates
    void SetX(double x) { mX = x; }
    void SetY(double y) { mY = y; }

    /// Getters for x and y coordinates
    double X() { return mX; }
    double Y() { return mY; }

};

#endif //SPARTYGNOME_VECTOR_H

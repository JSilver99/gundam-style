#ifndef _FRAME_H_
#define _FRAME_H_

/* Frame Definition - Modelling Layer
 *
 * Frame.h
 * fwk4gps version 4.0
 * gam666/dps901/gam670/dps905
 * June 25 2012
 * copyright (c) 2012 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "MathDecl.h" // for Matrix

//-------------------------------- Frame --------------------------------------
//
// The Frame class defines a reference frame in the Modelling Layer
//
class Frame {

    Matrix T;       // relative transformation wrt parent frame or world space
    Frame* parent; // points to parent frame, if any

  public:
    Frame();
	void   scale(float sx, float sy, float sz)   { T.scale(sx, sy, sz); }
	void   rotatex(float rad)                    { T.rotatex(rad); }
    void   rotatey(float rad)                    { T.rotatey(rad); }
    void   rotatez(float rad)                    { T.rotatez(rad); }
    void   rotate(const Vector& axis, float rad) { T.rotate(axis, rad); }
	void   translate(float x, float y, float z)  { T.translate(x, y, z); }
    void   orient(const Matrix& rot)             { T.orient(rot); }
    Vector position() const;
    Matrix rotation() const;
	Vector orientation(const Vector& v) const;
	Vector orientation(char c) const;
    Matrix world() const;
	void   attachTo(Frame* newParent);
    virtual ~Frame() {}
};

//-------------------------------- Shape ----------------------------
//
// A Shape is a Frame that has a Boundary
//
class Shape : public Frame {

    bool   sphere;
    bool   plane;
    bool   axisAligned;
    float  radius;
    float  distance;
    Vector normal;
    Vector minimum;
    Vector maximum;

public:
    Shape() : sphere(false), plane(false), axisAligned(false),
     radius(0), distance(0) {}
    void  scale(float, float, float);
    void  setRadius(float r);
    void  setRadius(float x, float y, float z);
    float getRadius() const { return radius; }
    void  setPlane(Vector n, float d);
    void  setAxisAligned(Vector min, Vector max);
    friend bool collision(const Shape* f1, const Shape* f2, Vector& d);
};

//-------------------------------- iSwitch -------------------------------------
//
// iSwitch is the Interface for a switchable design item
//
class iSwitch {
public:
    virtual bool isOn() const = 0;
};

#endif
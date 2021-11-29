#include "Point.h"

float Point::getX() const {
    return x;
}

void Point::setX(float x) {
    Point::x = x;
}

float Point::getY() const {
    return y;
}

void Point::setY(float y) {
    Point::y = y;
}

float Point::getZ() const {
    return z;
}

void Point::setZ(float z) {
    Point::z = z;
}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

float Point::distance(Point point2) {
    float x = (Point::x-point2.getX());
    float y = (Point::y-point2.getY());
    float z = (Point::z-point2.getZ());

    return sqRoot(x*x+y*y+z*z);
}



float Point::sqRoot(float number)
{
    int i;
    float x2,y;

    x2 = number * 0.5F;

//  Part with the help of quake 3 source code
    y  = number;
    i  = * ( int * ) &y;                       // evil floating point bit level hacking
    i  =  ( i >> 1 ) + 0x1fbd1df5;               // Lots of calculation and approximation
    y  = * ( float * ) &i;

//    Newton's method
//    y = (y - (((y * y) - number)/(2* y)));

// Simplified
    y = y/2 + x2/y;  // 1st iteration
    y = y/2 + x2/y;  // 2nd iteration
//    y = y/2 + x2/y;  // 3rd iteration

    return y;
}




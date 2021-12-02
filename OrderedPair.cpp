#include <cstdio>
#include "OrderedPair.h"

OrderedPair::OrderedPair(int x, int y) {
    this->x = x;
    this->y = y;
}

OrderedPair::OrderedPair(const OrderedPair &orderedPair) {
    this->x = orderedPair.x;
    this->y = orderedPair.y;
}

OrderedPair::~OrderedPair() {
    printf("\nInside ~Destructor");
};

int OrderedPair::getX() const{
    return x;
}

void OrderedPair::setX(int x) {
    this->x = x;
}

int OrderedPair::getY()  const{
    return y;
}

void OrderedPair::setY(int y) {
    this->y = y;
}

void OrderedPair::set(int x, int y) {
    this->x = x;
    this->y = y;
}

void OrderedPair::show() const{
    printf("(%d, %d)", x, y);
}


float OrderedPair::sqRoot(float number)
{
    int i;
    float x2,y;
    x2 = number * 0.5F;
    y  = number;
    i  = * ( int * ) &y;
    i  =  ( i >> 1 ) + 0x1fbd1df5;
    y  = * ( float * ) &i;
    y = y/2 + x2/y;
    y = y/2 + x2/y;
    return y;
}

float OrderedPair::getLength() const {
    return sqRoot(x*x+y*y);
}

OrderedPair::OrderedPair() {
    this->x=0;
    this->y=0;

}

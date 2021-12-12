#include <cstdio>
#include "OrderedPair.h"

OrderedPair::OrderedPair(){
    this->x=0;
    this->y=0;
}
OrderedPair::OrderedPair(int x, int y) {
    this->x = x;
    this->y = y;
}

OrderedPair::OrderedPair(const OrderedPair &orderedPair) {
    this->x = orderedPair.x;
    this->y = orderedPair.y;
}

OrderedPair::~OrderedPair() {
//    printf("\nInside ~Destructor");
};

int OrderedPair::getX() const{
    return x;
}

void OrderedPair::setX(int x) {
    this->x = x;
}

int OrderedPair::getY() const{
    return y;
}

void OrderedPair::setY(int y) {
    this->y = y;
}

void OrderedPair::set(int x, int y) {
    this->x = x;
    this->y = y;
}

void OrderedPair::show() const {
    printf("(%d, %d)", x, y);
}





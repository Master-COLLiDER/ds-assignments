#ifndef ASSIGNMENTS_STACK_H
#define ASSIGNMENTS_STACK_H

#include "OrderedPair.h"

struct Node {
    OrderedPair data;
    Node *next;
};

class Stack {
    Node *top;
public:
    Stack();

    ~Stack();

    bool push(const OrderedPair &data);

    OrderedPair pop();

    bool isEmpty();

    void display();

};

#endif
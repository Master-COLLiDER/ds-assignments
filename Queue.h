#ifndef ASSIGNMENTS_QUEUE_H
#define ASSIGNMENTS_QUEUE_H

#include "OrderedPair.h"

struct Node {
    OrderedPair info;
    Node *next;
};

class Queue {
    Node *front, *rear;
public:
    Queue();

    ~Queue();

    int enqueue(const OrderedPair &what);

    OrderedPair dequeue();

    void display();

    bool isEmpty();
};


#endif

#ifndef ASSIGNMENTS_QUEUE_H
#define ASSIGNMENTS_QUEUE_H

struct Node{
    int info;
    Node* next;
};

class Queue {
    Node * front, * rear;
public:
    Queue();

     ~Queue();
    int enqueue(int);
    int dequeue();
    void display();
    bool isEmpty();
};


#endif

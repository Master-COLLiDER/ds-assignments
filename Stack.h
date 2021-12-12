#ifndef ASSIGNMENT_STACK_H
#define ASSIGNMENT_STACK_H
template<typename T> class Stack {
    struct Node {
        T data;
        Node *next;

        Node() {
            next = nullptr;
        }
    } *top;

public:
    Stack();

    virtual ~Stack();

    bool push(T);

    T pop();

    bool isEmpty();

    void display();

};

#include "Stack.cpp"

#endif
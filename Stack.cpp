#ifndef ASSIGNMENT_STACK_CPP
#define ASSIGNMENT_STACK_CPP

#include <iostream>
#include "Stack.h"


template<typename T>
Stack<T>::Stack() {
    top = nullptr;
}

template<typename T>
Stack<T>::~Stack() {
    Node* temp;
    temp = top;
    while (top != nullptr)
    {
        top= top->next;
        delete temp;
        temp = top;
    }
}
template<typename T>
bool Stack<T>::push(T data) {
    Node *temp;
    temp = new Node();
    if (!temp) {
        std::cout << "\nStack Overflow" << std::endl;
        return false;
    }
    temp->data = data;
    temp->next = top;
    top = temp;
    return true;
}
template<typename T>
T Stack<T>::pop() {
    Node *temp;

    if (top == nullptr) {
        std::cout << "\nStack Underflow" << std::endl;
        exit(1);
    }

    temp = top;
    top = top->next;
    T data = temp->data;
    delete temp;
    return data;
}

template<typename T>
bool Stack<T>::isEmpty() {
    return top == nullptr;
}

#endif
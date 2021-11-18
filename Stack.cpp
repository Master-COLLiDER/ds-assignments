#include <iostream>
#include "Stack.h"

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    Node* temp;
    temp = top;
    while (top != NULL)
    {
        top= top->next;
        delete temp;
        temp = top;
    }
}

bool Stack::push(int data) {
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

int Stack::pop() {
    Node *temp;

    if (top == nullptr) {
        std::cout << "\nStack Underflow" << std::endl;
        return 0;
    }

    temp = top;
    top = top->next;
//    temp->next = nullptr;
    int data = temp->data;
    delete temp;
    return data;
}

bool Stack::isEmpty() {
    return top == nullptr;
}

void Stack::display() {
    Node *temp;
    if (top == nullptr) {
        std::cout << "\nStack is Empty!!";
    } else {
        temp = top;
        while (temp != nullptr) {
            std::cout << " ->" << temp->data;
            temp = temp->next;
        }
    }
}

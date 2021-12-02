#include <iostream>
#include "Stack.h"

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    Node* temp;
    temp = top;
    while (top != nullptr)
    {
        top= top->next;
        delete temp;
        temp = top;
    }
}

bool Stack::push(const OrderedPair &data) {
    Node *temp;
    temp = new Node;
    if (!temp) {
        std::cout << "\nStack Overflow" << std::endl;
        return false;
    }
    temp->data = data;
    temp->next = top;
    top = temp;
    return true;
}

OrderedPair Stack::pop() {
    Node *temp;

    if (top == nullptr) {
        std::cout << "\nStack Underflow" << std::endl;
        exit(0);
    }

    temp = top;
    top = top->next;
    temp->next = nullptr;
    OrderedPair data = temp->data;
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
            temp->data.show();
            temp = temp->next;
            std::cout << " ->";
        }
    }
}


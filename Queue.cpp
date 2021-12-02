#include "Queue.h"
#include <iostream>

Queue::Queue() {
    printf("Inside Constructor");
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue() {
    Node *temp;
    temp = front;
    printf("\nInside Destructor");
    while (temp != nullptr) {
        free(temp);
        temp = temp->next;
    }
}

int Queue::enqueue(const OrderedPair &what) {
    Node *temp;
    temp = (Node *) malloc(sizeof(Node));
    if (temp == nullptr)
        return 0;
    temp->info = what;
    temp->next = nullptr;

    if (rear != nullptr)
        rear->next = temp;
    else {
        front = temp;
        rear = temp;
    }
//    rear = temp;
    return 1;
}

OrderedPair Queue::dequeue() {
    OrderedPair value;
    Node *temp;
    temp = front;
    value = temp->info;
    if (front->next != nullptr)
        front = front->next;
    else {
        front = nullptr;
        rear = nullptr;
    }
    free(temp);
    return value;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

void Queue::display() {
    Node *temp;
    temp = front;
    printf("\nThe Queue: ");
    while (temp != NULL) {
        temp->info.show();
        printf("-> ");
        temp = temp->next;
    }

}

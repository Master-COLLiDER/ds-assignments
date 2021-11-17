#include "Queue.h"
#include <iostream>

Queue::Queue() {
    printf("Inside Constructor");
    front = NULL;
    rear = NULL;
}

Queue::~Queue() {
    Node *temp;
    temp = front;
    printf("\nInside Destructor");
    while (temp != NULL) {
        free(temp);
        temp = temp->next;
    }
}

int Queue::enqueue(int what) {
    Node *temp;
    temp = (Node *) malloc(sizeof(Node));
    if (temp == NULL)
        return 0;
    temp->info = what;
    temp->next = NULL;
    if (rear != NULL)
        rear->next = temp;
    else {
        front = temp;
        rear = temp;
    }

    rear = temp;
    return 1;
}

int Queue::dequeue() {
    int value;
    Node *temp;
    temp = front;
    value = temp->info;
    if (front->next != NULL)
        front = front->next;
    else {
        front = NULL;
        rear = NULL;
    }
    free(temp);
    return value;
}

bool Queue::isEmpty() {
    return front == NULL;
}

void Queue::display() {
    Node *temp;
    temp = front;
    printf("\nThe Queue: ");
    while (temp != NULL) {
        printf("%d->", temp->info);
        temp = temp->next;
    }

}

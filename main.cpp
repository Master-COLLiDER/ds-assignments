#include <iostream>
#include "Queue.h"

int main() {
    int c, data;
    Queue queue;
    printf("\n--Queue Program Menu--");
    do {
        printf("\n1.Enqueue\n2.Dequeue\n3.Display\n4.Is Empty\n5.Exit");
        printf("\nEnter your choice:");
        std::cin >> c;
        switch (c) {
            case 1:
                printf("Enter a data to enqueue: ");
                std::cin >> data;
                if (queue.enqueue(data)) {
                    printf("Successfully enqueued: %d.", data);
                } else
                    printf("Operation Failed!");
                break;
            case 2:
                printf("Dequeued: %d", queue.dequeue());
                break;
            case 3:
                queue.display();
                break;
            case 4:
                printf("\nQueue is ");
                printf(queue.isEmpty() ? "Empty." : "Not Empty.");
                break;
            case 5:
                break;
            default:
                printf("\nInvalid choice!!\n");
        }
    } while (c != 5);
    return 0;
}

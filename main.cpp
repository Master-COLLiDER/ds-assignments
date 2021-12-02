#include <iostream>
#include "Queue.h"

int main() {
    int c, x,y;
    OrderedPair data;
    Queue queue;
    printf("\n--Queue Program Menu--");
    do {
        printf("\n1.Enqueue\n2.Dequeue\n3.Display\n4.Is Empty\n5.Exit");
        printf("\nEnter your choice:");
        std::cin >> c;
        switch (c) {
            case 1:
                printf("Enter a data to enqueue: ");
                std::cin >> x>>y;
                data = OrderedPair(x,y);
                if (queue.enqueue(data)) {
                    printf("Successfully enqueued: (%d, %d).",x,y);
                } else
                    printf("Operation Failed!");
                break;
            case 2:
                printf("Dequeued: ");
                queue.dequeue().show();
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

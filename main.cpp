#include <iostream>
#include "Heap.h"

int main() {
    Heap heap(10);
    heap.insert_heap(4);

    if (heap.is_empty())
        printf("Empty Heap!");
    else
        heap.show();
    return 0;
}

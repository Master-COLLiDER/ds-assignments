#include <iostream>
#include "Heap.h"

int main() {
    Heap heap(10);
    heap.insert_heap(5);
    heap.insert_heap(4);
    heap.insert_heap(8);


    heap.delete_heap();

    if (heap.is_empty())
        printf("Empty Heap!");
    else
        heap.show();
    return 0;
}

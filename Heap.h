#ifndef ASSIGNMENTS_HEAP_H
#define ASSIGNMENTS_HEAP_H


class Heap {
    int *data;
    int count, MAX;

public:
    Heap()
    {
        MAX = 0;
        count = 0;
        data = NULL;
    }
    Heap(int);
    int insert_heap(int);
    int Heapify();
    int delete_heap();
    bool is_empty();
    void show();
};


#endif //ASSIGNMENTS_HEAP_H

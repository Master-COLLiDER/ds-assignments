#include <iostream>
#include "Heap.h"

Heap::Heap(int max_need) {
    count = 0;
    if (max_need < 1) {
        MAX = 0;

        data = NULL;
    } else {
        data = (int *) malloc(sizeof(int) * max_need);
        if (data == NULL)
            MAX = 0;
        else
            MAX = max_need;
    }
}

int Heap::insert_heap(int value) {
    int cur, par;
    if (count == MAX)
        return 0;
    data[count] = value;
    cur = count++;
    par = (cur - 1) / 2;
    while (par != cur) {
        if (data[par] >= data[cur])
            break;
        data[cur] = data[par];
        data[par] = value;
        cur = par;
        par = (cur - 1) / 2;
    }
    return 1;
}

int Heap::delete_heap() {
    if (count < 1)
        return 0;
    int temp;
    temp = data[0];
    count--;
    if (count > 0) {
        int child = 1, cur = 0, value;
        value = data[count];
        data[0] = value;
        while (cur<=count-1) {
            if (data[child] <= data[cur])
                break;
            data[cur] = data[child];
            data[child] = value;
            cur = child;
            child = (cur * 2) + 1;
        }
    }
    return temp;
}

//int Heap::Heapify() {
//
//    int temp, i, j;
//    for (i = 1; i < count; i++) {
//        if (data[i] > data[(i - 1) / 2]) {
//            j = i;
//            while (data[j] > data[(j - 1) / 2]) {
//                temp = data[j];
//                data[j] = data[(j - 1) / 2];
//                data[(j - 1) / 2] = temp;
//                j = (j - 1) / 2;
//            }
//        }
//    }
//
//    return 1;
//}

//int Heap::delete_heap() {
//    if (count<1)
//        return 0;
//    int temp;
//    temp = data[0];
//    data[0] = data[--count];
//    Heapify();
//    return temp;
//}

bool Heap::is_empty() {
    return count == 0;
}

void Heap::show() {

    int i;
    for (i = 0; i < count; i++) {
        printf("[%d ], ", data[i]);
    }
}

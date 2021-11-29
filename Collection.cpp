
#include <cstdlib>
#include "Collection.h"

Collection::Collection() {
    MAX = 0;
    count = 0;
    data = nullptr;
}

Collection::Collection(int n) {
    if (n < 1) {
        MAX = 0;
        count = 0;
        data = nullptr;
    } else {
        data = (CURRENT_TYPE *) malloc(sizeof(CURRENT_TYPE) * n);
        if (data == nullptr) {
            MAX = 0;
            count = 0;
        } else {
            MAX = n;
            count = 0;
        }
    }
}

Collection::~Collection() {
    delete data;
}

bool Collection::isEmpty() {
    return count == 0;
}

int Collection::insert_pos(CURRENT_TYPE what, int pos) {
    int i;
    if (count == MAX)
        return 0;
    if ((pos < 1) || (pos > count + 1))
        return 0;
    if (pos - 1 == count)
        data[count] = what;
    else {
        for (i = count; i >= pos; i--)
            data[i] = data[i - 1];
        data[pos - 1] = what;
    }

    count++;
    return 1;
}

int Collection::insert_beginning(float what) {
    return insert_pos(what, 1);
}

int Collection::insert_end(float what) {
    return insert_pos(what, count + 1);
}

int Collection::insert_after(float what, float after_which) {
    return insert_pos(what, indexOf(after_which) + 1);
}

int Collection::insert_before(float what, float before_which) {
    return insert_pos(what, indexOf(before_which));
}


CURRENT_TYPE Collection::delete_pos(int pos) {
    int i;
    float temp;
    if (count < 1)
        return NULL;
    if ((pos < 1) || (pos > count))
        return NULL;

    temp = data[pos - 1];

    if (pos == count)
        count--;
    else {
        for (i = pos - 1; i < count - 1; i++)
            data[i] = data[i + 1];
        count--;
    }
    return temp;
}

CURRENT_TYPE Collection::delete_beginning() {
    return delete_pos(1);
}

CURRENT_TYPE Collection::delete_end() {
    return delete_pos(count - 1);
}

CURRENT_TYPE Collection::delete_data(float which) {
    return delete_pos(indexOf(which));
}

int Collection::indexOf(float which) {
    int i = 0;
    if (count == 0)
        return -1;
    while ((data[i] != which) && i < count)
        i++;
    return i >= count ? -1 : i + 1;
}


void Collection::bubbleSort() {
    int i, j;
    float temp;
    for (i = count - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            St_Comp:
            if (data[j] > data[j + 1]) {
                St_Asn_1:
                temp = data[j];
                St_Asn_2:
                data[j] = data[j + 1];  //St_Asn_2
                St_Asn_3:
                data[j + 1] = temp;  //St_Asn_3
            }
        }
    }
//    St_perf:

}


std::ostream &operator<<(std::ostream &os, const Collection &collection) {
    os << "\nMAX: " << collection.MAX;
    os << "\tCount: " << collection.count;
    os << "\nData: ";
    for (int i = 0; i < collection.count; i++) {
        os << collection.data[i] << (((i + 1) != collection.count) ? ", " : "");
    }
    return os;
}






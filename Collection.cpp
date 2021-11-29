
#include <cstdlib>
#include "Collection.h"

Collection::Collection() {
    Collection::MAX = 0;
    Collection::count = 0;
    Collection::data = nullptr;
}

Collection::Collection(int n) {
    if (n < 1) {
        Collection::MAX = 0;
        Collection::count = 0;
        Collection::data = nullptr;
    } else {
        Collection::data = (CURRENT_TYPE *)malloc(sizeof(CURRENT_TYPE) * n);
        if (Collection::data == nullptr) {
            Collection::MAX = 0;
            Collection::count = 0;
        } else {
            Collection::MAX = n;
            Collection::count = 0;
        }
    }
}

Collection::~Collection() {
    delete Collection::data;
}

bool Collection::isEmpty() {
    return Collection::count==0;
}

int Collection::insert_pos(CURRENT_TYPE what,int pos){
    if(Collection::count==MAX)
        return 0;
    if ((pos<1)||(pos>Collection::count+1))
        return 0;
    for (int i = Collection::count;i>pos-1;i--)
        data[i]=data[i-1];
    data[pos-1]=what;
    count++;
    return 1;
}

int Collection::insert_beginning(float what) {
    return 0;
}

int Collection::insert_end(float what) {
    return 0;
}

int Collection::insert_after(float what, float after_which) {
    return 0;
}

int Collection::insert_before(float what, float before_which) {
    return 0;
}

CURRENT_TYPE Collection::delete_beginning() {
    return 0;
}

CURRENT_TYPE Collection::delete_end() {
    return 0;
}

CURRENT_TYPE Collection::delete_pos(int position) {
    return 0;
}

CURRENT_TYPE Collection::delete_data(float which) {
    return 0;
}

std::ostream &operator<<(std::ostream &os, const Collection &collection) {
    os << "\nMAX: " << collection.MAX;
    os << "\nCount: " << collection.count;
    os << "\nData: ";
    for (int i = 0; i < collection.count; i++) {
        os<<collection.data[i]<<", ";
    }
    return os;
}



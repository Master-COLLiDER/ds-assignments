#include <iostream>
#include "Collection.h"


int main() {
    Collection collection = Collection(10);

    collection.insert_beginning(41);
    collection.insert_beginning(11);
    collection.insert_beginning(455);
    collection.insert_beginning(235);
    collection.insert_beginning(231);
    collection.insert_beginning(526.1);
    collection.insert_beginning(22);
    collection.insert_beginning(33);
    collection.insert_beginning(33);
    collection.insert_before(55, 33);
    std::cout << collection << std::endl;


    collection.bubbleSort();

//    collection.delete_data(526.1);
    std::cout << collection << std::endl;
    return 0;

}

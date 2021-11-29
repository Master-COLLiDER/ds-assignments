#include <iostream>
#include "Collection.h"


int main() {
    Collection collection = Collection(10);
    collection.insert_pos(21,1);
    collection.insert_pos(54,1);
    collection.insert_pos(4235,1);
    collection.insert_pos(234,1);
    std::cout << "Hello, World!" << std::endl;
    std::cout << collection << std::endl;
    return 0;
    
}

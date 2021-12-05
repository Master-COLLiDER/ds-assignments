#include <iostream>
#include "Collection.h"

void printMenu();


int main() {

    int n, choice = 0, pos,x,y;
    CURRENT_TYPE data;

    std::cout << "Enter the Collection size: ";
    std::cin >> n;

    Collection collection = Collection(n);


    while (choice != 5) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
//                std::cout << "Enter the value (x,y) to insert: ";
//                std::cin >> x>>y;
//                data = OrderedPair(x,y);
//                std::cout << "In which position: ";
//                std::cin >> pos;
//                if (collection.insert_pos(data, pos)) {
//                    std::cout << "Successfully Inserted "; data.show();std::cout << " in " << pos << "-th position.";
//                } else {
//                    std::cout << "Failed to insert "; data.show();std::cout << pos << "-th position";
//                }

                collection.insert_beginning(OrderedPair(85,64));
                collection.insert_beginning(OrderedPair(637,34));
                collection.insert_beginning(OrderedPair(1245,21));
                collection.insert_beginning(OrderedPair(43,566));
                collection.insert_beginning(OrderedPair(345,11));
                break;
            case 2:
                collection.displayData();
                break;
            case 3:
                collection.quickSort();
                break;
            case 4:
                std::cout << "Enter the position for the value to delete: ";
                std::cin >> pos;
                std::cout << "Deleted "; collection.delete_pos(pos);std::cout << " in " << pos << "-th position.";

                break;
            case 5:
                break;
            default:
                std::cout << "\nInvalid Choice!!!";
        }
    }

    return 0;

}

void printMenu() {
    std::cout << "\nRoll No.: CSM21002\n";
    std::cout << ":::Collection Class Menu:::\n";
    std::cout << "1. Insert\n";
    std::cout << "2. Display\n";
    std::cout << "3. Quick Sort\n";
    std::cout << "4. Delete\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your Choice: ";
}
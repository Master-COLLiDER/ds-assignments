#include <iostream>
#include "Collection.h"

void printMenu();


int main() {

    int n, choice = 0, pos;
    CURRENT_TYPE data;

    std::cout << "Enter the Collection size: ";
    std::cin >> n;

    Collection collection = Collection(n);


    while (choice != 5) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> data;
                std::cout << "In which position: ";
                std::cin >> pos;
                if (collection.insert_pos(data, pos)) {
                    std::cout << "Successfully Inserted " << data << " in " << pos << "-th position.";
                } else {
                    std::cout << "Failed to insert " << data << " in " << pos << "-th position";
                }
                break;
            case 2:
                collection.displayData();
                break;
            case 3:
                collection.bubbleSort();
                break;
            case 4:
                std::cout << "Enter the position for the value to delete: ";
                std::cin >> pos;
                std::cout << "Deleted " << collection.delete_pos(pos) << " in " << pos << "-th position.";

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
    std::cout << "3. Bubble Sort\n";
    std::cout << "4. Delete\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your Choice: ";
}
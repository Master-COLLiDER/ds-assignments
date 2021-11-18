#include "Stack.h"
#include <iostream>

int main() {
    Stack stack = Stack();
    int ch;
    int data;
    do {
        std::cout << "\nStack Program Menu\n";
        std::cout << "1.Push an Element.\n";
        std::cout << "2.Pop an Element.\n";
        std::cout << "3.Display Stack.\n";
        std::cout << "4.Check isEmpty\n";
        std::cout << "5.Exit\n";
        std::cout << "Enter your Choice:";
        std::cin >> ch;

        switch (ch) {
            case 1:
                std::cout << "Enter an element to Push: ";
                std::cin >> data;
                if (stack.push(data)) {
                    std::cout << "Successfully pushed " << data << std::endl;
                } else {
                    std::cout << "Operation Failed!" << std::endl;
                }
                break;
            case 2:
                data = stack.pop();
                if (data) {
                    std::cout << "Element popped : " << data << std::endl;
                } else {
                    std::cout << "Operation Failed!" << std::endl;
                }
                break;
            case 3:
                std::cout << "Elements in the Stack are: ";
                stack.display();
                break;
            case 4:
                std::cout << "Stack is " << (stack.isEmpty() ? "Empty" : "not Empty") << std::endl;
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid Choice...";
                break;
        }
    } while (ch != 5);


    return 0;
}

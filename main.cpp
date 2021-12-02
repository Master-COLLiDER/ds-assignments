#include "Stack.h"
#include <iostream>

int main() {
    Stack stack = Stack();
    int ch,x,y;
    OrderedPair data;
    do {
        std::cout << "\nStack Program Menu\n";
        std::cout << "1.Push an (x,y) Pair.\n";
        std::cout << "2.Pop an Element.\n";
        std::cout << "3.Display Stack.\n";
        std::cout << "4.Check isEmpty\n";
        std::cout << "5.Exit\n";
        std::cout << "Enter your Choice:";
        std::cin >> ch;

        switch (ch) {
            case 1:
                std::cout << "Enter an (x,y) to Push: ";
                std::cin >>x>>y;
                data = OrderedPair(x,y);
                if (stack.push(data)) {
                    std::cout << "Successfully pushed "; data.show();std::cout<< std::endl;
                } else {
                    std::cout << "Operation Failed!" << std::endl;
                }
                break;
            case 2:
                data = stack.pop();
                std::cout << "Element popped : "; data.show(); std::cout<< std::endl;

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

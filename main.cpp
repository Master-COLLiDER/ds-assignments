#include <iostream>
#include "Point.h"

int main() {
    Point point1 = Point(10, 10, 10);
    Point point2 = Point(0, 0, 0);
    std::cout << "Distance : "<<point1.distance(point2);

    return 0;
}

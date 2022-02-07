#include <iostream>

namespace CSM21002 {
    void swap(float &x, float &y) {
        x = x + y;
        y = x - y;
        x = x - y;
    }

    void bubbleSort(float data[], int count) {
        for (int i = count - 1; i > 0; i--)
            for (int j = 0; j < i; j++)
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
    }
}

int main() {
    float data[] = {43.34, 234.13, 2563, 234, 521};

    CSM21002::bubbleSort(data, 5);
    for (int i = 0; i < 5; ++i) {
        std::cout<<" "<<data[i];
    }
    return 0;
}


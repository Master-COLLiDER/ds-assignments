#include <iostream>

class diagonal_matrix {
    int n, *data;
public:
    diagonal_matrix();

    diagonal_matrix(const int &n);

    ~diagonal_matrix();

    bool set_element(const int &r, const int &c, const int &value);

    int get_element(const int &r, const int &c);

    void display();

    void set_matrix();

};

diagonal_matrix::diagonal_matrix() {
    n = 0;
    data = nullptr;
}

diagonal_matrix::diagonal_matrix(const int &n) {
    int i;
    if (n < 1) {
        {
            this->n = 0;
            data = nullptr;
        }
    } else {
        this->n = n;
        data = new int[n];
        for (i = 0; i < n; ++i) {
            data[i] = 0;
        }

    }
}



diagonal_matrix::~diagonal_matrix() {
    delete[] data;
}

bool diagonal_matrix::set_element(const int &r, const int &c, const int &value) {
    if (r < 1 || c < 1 || r > n || c > n) {
        printf("\n r or c is Invalid");
        exit(1);
    }
    if (r == c) {
        data[c - 1] = value;
        return true;
    }
    return false;
}

int diagonal_matrix::get_element(const int &r, const int &c) {
    if (r < 1 || c < 1 || r > n || c > n) {
        printf("\n r or c is Invalid");
        exit(1);
    }
    if (r == c) {
        return data[c - 1];
    } else
        return 0;
}

void diagonal_matrix::display() {
    int i, j;
    printf("Matrix : \n");
    for (i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                printf("%d ", data[i]);
            else
                printf("0 ");
        }
        printf("\n");
    }
}

void diagonal_matrix::set_matrix() {
    int i, value;
    printf("Set Matrix:");
    for (i = 0; i < n; ++i) {
        printf("\nEnter element of %d-th row and %d-th column:  ", i + 1, i + 1);
        std::cin >> value;
        data[i] = value;
    }
}


int main() {
    diagonal_matrix *matrix;
    int ch = 0, r, c, value;
    printf("Enter the size of the matrix: ");
    std::cin >> value;

    matrix = new diagonal_matrix(value);

    while (ch != 5) {
        printf("\nRoll No.: CSM21002\n:::Diagonal Matrix:::\n1.Set Matrix\n2.Set Element\n3.Get Element\n4.Display Matrix\n5.Exit\n:Enter your choice: ");
        std::cin >> ch;
        switch (ch) {
            case 1:
                matrix->set_matrix();
                break;
            case 2:
                printf("Enter row , column and Value respectively");
                std::cin >> r >> c >> value;
                if (matrix->set_element(r, c, value))
                    printf("Successful");
                else
                    printf("Can't set data in (%d,%d)", r, c);
                break;
            case 3:
                printf("Enter row , column");
                std::cin >> r >> c;
                printf("Element in (%d,%d) = %d", r, c, matrix->get_element(r, c));
                break;
            case 4:
                matrix->display();
                break;
            case 5:
                break;
            default:
                printf("Invalid Choice!!");
        }
    }
    delete matrix;
    return 0;
}

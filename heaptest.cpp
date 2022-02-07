#include <iostream>

class Heap {
    int *data;
    int count, MAX;

public:
    Heap()
    {
        MAX = 0;
        count = 0;
        data = NULL;
    }
    Heap(int);
    int insert_heap(int);
    int delete_heap();
    bool is_empty();
    int heapify();
    void show() {
        int i;
        for (i = 0; i < count; i++) {
            printf("[%d ], ", data[i]);
        }
    }
};

Heap::Heap(int max_need) {
    count = 0;
    if (max_need < 1) {
        MAX = 0;

        data = NULL;
    } else {
        data = (int *) malloc(sizeof(int) * max_need);
        if (data == NULL)
            MAX = 0;
        else
            MAX = max_need;
    }
}

int Heap::insert_heap(int value) {
    int cur, par;
    if (count == MAX)
        return 0;

    data[count] = value;
    cur = count++;
    par = (cur - 1) / 2;
    while (par != cur) {
        if (data[par] <= data[cur])
            break;
        data[cur] = data[par];
        data[par] = value;
        cur = par;
        par = (cur - 1) / 2;
    }
    return 1;
}

int Heap::delete_heap() {
    if (count < 1)
        return 0;
    int  temp = data[0];
    if(--count>0) {
        data[0] = data[count];
        heapify();
    }
    return temp;
}

int Heap::heapify() {

    int temp, i, j;
    for (i = 1; i < count; i++) {
        if (data[i] < data[(i - 1) / 2]) {
            j = i;
            while (data[j] < data[(j - 1) / 2]) {
                temp = data[j];
                data[j] = data[(j - 1) / 2];
                data[(j - 1) / 2] = temp;
                j = (j - 1) / 2;
            }
        }
    }
    return 1;
}


bool Heap::is_empty() {
    return count == 0;
}



int main() {
    Heap h1(10);
    int ch,s,n,st;
    do {

        printf("\n1.insert\n2.show\n3.Delete\n4.Exit\n");

        scanf("%d",&ch);
        switch(ch) {
            case 1:

                printf("Enter number \n");
                scanf("%d",&n);
                s=h1.insert_heap(n);
                if(s==0) {
                    printf("failed\n");
                } else {
                    printf(" Sucessfully inserted\n",s);
                }
                break;
            case 2:
                h1.show();
                break;

            case 3:
                if(h1.is_empty()==1) {
                    printf("EMPTY\n");
                } else {
                    std::cout<<h1.delete_heap();
                }
                break;

            case 4:
                return 0;
            default:
                printf("Try again !!!\n");
        }
    } while(1);

    return 0;

}
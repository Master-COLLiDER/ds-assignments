
#include <iostream>
#include "Collection.h"
#include "Stack.h"

Collection::Collection() {
    MAX = 0;
    count = 0;
    data = nullptr;
}

Collection::Collection(int n) {
    if (n < 1) {
        MAX = 0;
        count = 0;
        data = nullptr;
    } else {
        data = (CURRENT_TYPE *) malloc(sizeof(CURRENT_TYPE) * n);
        if (data == nullptr) {
            MAX = 0;
            count = 0;
        } else {
            MAX = n;
            count = 0;
        }
    }
}

Collection::~Collection() {
    free(data);
}

bool Collection::isEmpty() {
    return count == 0;
}

int Collection::insert_pos(CURRENT_TYPE what, int pos) {
    int i;
    if (count == MAX) {
        std::cout << "\nFailed to insert " << what << " in " << pos << "-th position";
        return 0;
    }
    if ((pos < 1) || (pos > count + 1)) {
        std::cout << "\nFailed to insert " << data << " in " << pos << "-th position";;
        return 0;
    }
    if (pos - 1 == count)
        data[count] = what;
    else {
        for (i = count; i >= pos; i--)
            data[i] = data[i - 1];
        data[pos - 1] = what;
    }
    count++;
    std::cout << "\nSuccessfully Inserted " << what << " in " << pos << "-th position.";
    return 1;
}

int Collection::insert_beginning(float what) {
    return insert_pos(what, 1);
}

int Collection::insert_end(float what) {
    return insert_pos(what, count + 1);
}

int Collection::insert_after(float what, float after_which) {
    return insert_pos(what, indexOf(after_which) + 1);
}

int Collection::insert_before(float what, float before_which) {
    return insert_pos(what, indexOf(before_which));
}


CURRENT_TYPE Collection::delete_pos(int pos) {
    int i;
    float temp;
    if (count < 1)
        return NULL;
    if ((pos < 1) || (pos > count))
        return NULL;

    temp = data[pos - 1];

    if (pos == count)
        count--;
    else {
        for (i = pos - 1; i < count - 1; i++)
            data[i] = data[i + 1];
        count--;
    }
    return temp;
}

CURRENT_TYPE Collection::delete_beginning() {
    return delete_pos(1);
}

CURRENT_TYPE Collection::delete_end() {
    return delete_pos(count - 1);
}

CURRENT_TYPE Collection::delete_data(float which) {
    return delete_pos(indexOf(which));
}

int Collection::indexOf(float which) {
    int i = 0;
    if (count == 0)
        return -1;
    while ((data[i] != which) && i < count)
        i++;
    return i >= count ? -1 : i + 1;
}


void Collection::bubbleSort() {
    int St_Comp=0,St_Asn_1=0,St_Asn_2=0,St_Asn_3=0;
    int i, j;
    float temp;
    for (i = count - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {

    St_Comp:  if (data[j] > data[j + 1]) {             St_Comp++;
            St_Asn_1:   temp = data[j];             St_Asn_1++;
            St_Asn_2:   data[j] = data[j + 1];      St_Asn_2++;
            St_Asn_3:   data[j + 1] = temp;         St_Asn_3++;
        }
        }
    }
    std::cout << "Data sorted!\n";
    St_perf:
    std::cout << "St_Comp :" << St_Comp << " times.\n";
    std::cout << "St_Asn_1 :" << St_Asn_1 << " times.\n";
    std::cout << "St_Asn_2 :" << St_Asn_2 << " times.\n";
    std::cout << "St_Asn_3 :" << St_Asn_3 << " times.\n";

}



void Collection::displayData() {

    if(count){
        std::cout<<"Data : ";
        for (int i = 0; i < count; i++) {
            std::cout << data[i] << (((i + 1) != count) ? ", " : "");
        }
    } else{
        std::cout<<"Empty!";
    }

}

int Collection::getMax() const {
    return MAX;
}

void Collection::insertionSort() {
    int i,j;
    CURRENT_TYPE value;
    for (i = 1; i < count; i++) {
        value = data[i];
        for (j = i; j>=0 && data[j-1] > value ; j--) {
            data[j] = data[j-1];
        }
        if (j!=i)
            data[j]=value;
    }
}

void Collection::quickSort() {
    Stack whereto;
    OrderedPair cur_op = OrderedPair(0,count-1); //cur_op is an ordered pair
    int start,end,position,left,right;
    float Pivot;
    whereto.push(cur_op);
    while(!whereto.isEmpty())
    {
        cur_op=whereto.pop();
        start = cur_op.getX();
        end = cur_op.getY();
        Pivot= data[start];
        position=start;
        left=start+1;
        right=end;
        while(left<right)
        {
            for( ;right>left; right--) // Ensure that element towards right of Pivot are bigger
            {
                if(data[right]<Pivot)
                {
                    data[position]=data[right];
                    data[right]=Pivot;
                    position=right;
                    right--;
                    break;
                }
            }
            for(  ; left < right; left++)   // Ensure that element towards left of Pivot are smaller
            {
                if(data[left]>=Pivot)
                {
                    data[position]=data[left];
                    data[left]=Pivot;
                    position=left;
                    left++;
                    break;
                }
            }
        } // End of main loop for Positioning the Pivot element
        if((position+1)<end)
        {
            cur_op=OrderedPair(position+1, end);
            whereto.push(cur_op);
        }
        if(start<(position-1))
        {
            cur_op=OrderedPair(start, position-1);
            whereto.push(cur_op);
        }


    }
}

void Collection::selectionSort() {
    int i,j,current_minimum;
    CURRENT_TYPE temp;
    for(i=0;i<count-1;i++){
        current_minimum = i;
        for (j = i+1; j < count; j++) {
            if (data[current_minimum]>data[j]){
                current_minimum=j;
            }
        }
        if(current_minimum!=i){
            temp = data[i];
            data[i] = data[current_minimum];
            data[current_minimum] = temp;
        }
    }
}





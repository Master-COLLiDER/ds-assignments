#include <iostream>
using namespace std;

// The Queue class declaration used in radixSort()
class Queue {
    struct Node {
        int info;
        Node *next;
    } *front, *rear;

public:
    Queue();
    ~Queue();
    int enqueue(int);
    int dequeue();
    bool isEmpty();
};

//The queue class definition

//The default constructor
Queue::Queue() {
    front = NULL;
    rear = NULL;
}

//The Destructor
Queue::~Queue() {
    Node *temp;
    temp = front;
    while (temp != NULL) {
        free(temp);
        temp = temp->next;
    }
}

//Enqueue function returns 1 if success 0 if failed
int Queue::enqueue(int what) {
    Node *temp;
    temp = (Node *) malloc(sizeof(Node));
    if (temp == NULL)
        return 0;
    temp->info = what;
    temp->next = NULL;
    if (rear != NULL)
        rear->next = temp;
    else {
        front = temp;
    }
    rear = temp;
    return 1;
}

//Dequeue function returns the dequeued value
int Queue::dequeue() {
    int value;
    Node *temp = front;

    value = temp->info;
    if (front->next != NULL)
        front = front->next;
    else {
        front = NULL;
        rear = NULL;
    }
    free(temp);
    return value;
}
//isEmpty() function can be used to check if a queue is empty
bool Queue::isEmpty() {return front == NULL;}
//End of Queue Class definition

//Collection class declaration
class Collection {
    int MAX, count;
    int *data;
public:
    Collection();
    Collection(int n);
    ~Collection();

    int getCount() const;
    int getMax() const;
    bool isEmpty();

    int insert_pos(int what, int position);
    int insert_beginning(int what);
    int insert_end(int what);
    int insert_after(int what, int after_which);
    int insert_before(int what, int before_which);
    int delete_beginning();
    int delete_end();
    int delete_pos(int position);
    int delete_data(int which);
    int indexOf(int which);

    int radixSort();

    void display();
};

//The Collection class definitions

//this function is the default constructor of collection
Collection::Collection() {
    MAX = 0;
    count = 0;
    data = NULL;
}

//this constructor take an integer input
//if the input n is non negative then n int location is allocated
//and MAX is set to n
Collection::Collection(int n) {
    count = 0;
    if (n < 1) {
        MAX = 0;
        data = NULL;
    } else {
        data = (int *) malloc(sizeof(int) * n);
        if (data == NULL) {
            MAX = 0;
        } else {
            MAX = n;
        }
    }
}

//Destructor of Collection Class frees the allocated memory pointed by data pointer
Collection::~Collection() {
    free(data);
}

//this function can be used to check if collection is empty
bool Collection::isEmpty() {return count == 0;}

//insert_pos takes input int what and int pos
//and inserts what to position pos in collection if pos given valid
int Collection::insert_pos(int what, int pos) {
    int i;
    if (count == MAX) {
        return 0;
    }
    if ((pos < 1) || (pos > count + 1)) {
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
    return 1;
}

//These functions uses insert_pos() function
int Collection::insert_beginning(int what) { return insert_pos(what, 1); }
int Collection::insert_end(int what) { return insert_pos(what, count + 1); }
int Collection::insert_after(int what, int after_which) { return insert_pos(what, indexOf(after_which) + 1); }
int Collection::insert_before(int what, int before_which) { return insert_pos(what, indexOf(before_which)); }

//takes input pos and removes element from pos position in collection
//if given pos is valid
int Collection::delete_pos(int pos) {
    int i;
    if (count < 1)
        return 0;
    if ((pos < 1) || (pos > count))
        return 0;

    if (pos == count) {
        count--;
    } else {
        for (i = pos - 1; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }
    return 1;
}

//These functions uses delete_pos() function
int Collection::delete_beginning() { return delete_pos(1); }
int Collection::delete_end() { return delete_pos(count); }
int Collection::delete_data(int which) { return delete_pos(indexOf(which)); }

//indexOf() Returns the index of given input int which if which is found
//the data or returns -1 if not found
//this function is used in functions: insert_after() , insert_before(), delete_data()
int Collection::indexOf(int which) {
    int i = 0;
    if (count == 0)
        return -1;
    while ((data[i] != which) && i < count)
        i++;
    return i >= count ? -1 : i + 1;
}

//Getter methods for MAX and Count
int Collection::getMax() const {return MAX;}
int Collection::getCount() const {return count;}


//Display/Show function for Collection class
void Collection::display() {

    if (count) {
        cout << "\n Collection Data : ";
        for (int i = 0; i < count; i++) {
            cout << data[i] << (((i + 1) != count) ? ", " : "");
        }
    } else {
        cout << "\nCollection is Empty!";
    }

}

//Radix sort function
//the above queue data structure is used here
//this function sorts the data given that elements are integers
int Collection::radixSort() {
    if (count<1)
        return 0;

    int maximum = data[0],minimum = data[0],maxDigit,digits = 0,power,cDigit,i,k,cNum,container;
    Queue P[10]; //the declaration of array of queue

    //this loop is used to find the larges element in the collection
    for ( i = 1; i < count; i++) {
        if (maximum < data[i])
            maximum = data[i];

        if (minimum > data[i])
            minimum = data[i];
    }

    //this part is used to change -ve container number +ve
    if (minimum < 0) {
        minimum = ~minimum + 1;
    }

    maxDigit = minimum>maximum?minimum:maximum;


    //This loop is used to find how many digits maxDigit integer has
    while (maxDigit > 0) {
        digits++;
        maxDigit /= 10;
    }

    //this loop will digits times
    for (cDigit = 1, power = 1; cDigit <= digits; cDigit++, power *= 10) {
        for (i = 0; i < count; i++) {
            cNum = data[i];
            // num/power % 10 is used to find the remainder of currentDigit / 10
            container = ((cNum / power) % 10);

            //this part is used to change -ve container number +ve
            if (container < 0) {
                container = ~container + 1;
            }

            P[container].enqueue(cNum);
        }
        k = 0;

        //In this loop every value stored inside each queue is dequeued to data
        for (i = 0; i < 10; i++) {
            while (!P[i].isEmpty()) {
                data[k] = P[i].dequeue();
                k++;
            }
        }
    }

    //This part sorts -ve number left side and +ve number right side of the array
    for (i = 0,k=-1; i < count; i++) {
        if(data[i]<0)
        {
            P[0].enqueue(data[i]);
            k++;
        }
        else{
            P[1].enqueue(data[i]);
        }
    }
    i = k+1;
    while(i<count){
        data[i] = P[1].dequeue();
        i++;
    }
    while(k>=0){
        data[k] = P[0].dequeue();
        k--;
    }
    // End here

    return 1;
}


int main() {

    int n, choice = 0, pos;
    int data;

    cout << "Enter the Collection size: ";
    cin >> n;

    Collection collection = Collection(n);


    while (choice != 5) {
        cout << "\nRoll No.: CSM21002\n";
        cout << ":::Collection Class with Radix Sort:::\n";
        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Radix Sort\n";
        cout << "4. Delete\n";
        cout << "5. Exit\n";
        cout << "Enter your Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
//                cout << "\nEnter the value to insert: ";
//                cin >> data;
//                if(collection.insert_beginning(data))
//                    cout<<"\nSuccessfully inserted: "<<data<<"in beginning of the collection.";
//                else
//                    cout<<"\nFailed to insert: "<<data;


//                cout << "In which position: ";
//                cin >> pos;
//                if(collection.insert_pos(data,pos))
//                    cout<<"Successfully inserted: "<<data<<"in position: "<<pos;
//                else
//                    cout<<"Failed to insert: "<<data<<" in position: "<<pos;


                collection.insert_end(20);
                collection.insert_end(345);
                collection.insert_end(66);
                collection.insert_end(76);
                collection.insert_end(623);
                collection.insert_end(56);
                break;
            case 2:
                collection.display();
                break;
            case 3:
                if (collection.radixSort())
                    cout << "\nData Sorted!";
                break;
            case 4:
                cout << "\nEnter the position for the value to delete: ";
                cin >> pos;
                cout << "\nDeleted " << collection.delete_pos(pos) << " in " << pos << "-th position.";
                break;
            case 5:
                return 0;
            default:
                cout << "\nInvalid Choice!!!";
        }
    }

    return 0;

}


struct Node {
    int data;
    Node *next;
};

class Stack {
    Node *top;
public:
    Stack();

    ~Stack();

    bool push(int);

    int pop();

    bool isEmpty();

    void display();

};

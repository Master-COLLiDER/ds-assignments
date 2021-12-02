#ifndef ORDERED_PAIR_H
#define ORDERED_PAIR_H


class OrderedPair {
    int x, y;
public:
    OrderedPair(int x, int y);

    OrderedPair(const OrderedPair &orderedPair);

    ~OrderedPair();

    void setX(int x);

    void setY(int y);

    void set(int x = 0, int y = 0);

    int getX();

    int getY();

    void show();



};


#endif //ORDERED_PAIR_H

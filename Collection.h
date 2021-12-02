#ifndef COLLECTION_H
#define COLLECTION_H

#include "OrderedPair.h"

#define CURRENT_TYPE OrderedPair


class Collection {
    int MAX, count;
    CURRENT_TYPE *data;
public:
    Collection();

    Collection(int n);

    ~Collection();

    int getMax() const;

    bool isEmpty();

    int insert_pos(const CURRENT_TYPE &what, int position);

    int insert_beginning(const CURRENT_TYPE &what);

    int insert_end(const CURRENT_TYPE &what);

    int insert_after(const CURRENT_TYPE &what, const CURRENT_TYPE &after_which);

    int insert_before(const CURRENT_TYPE &what, const CURRENT_TYPE &before_which);

    CURRENT_TYPE delete_beginning();

    CURRENT_TYPE delete_end();

    CURRENT_TYPE delete_pos(int position);

    CURRENT_TYPE delete_data(const CURRENT_TYPE &which);

    int indexOf(const CURRENT_TYPE &which);

    void bubbleSort();

    void displayData();

};


#endif //COLLECTION_H

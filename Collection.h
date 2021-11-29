#ifndef COLLECTION_H
#define COLLECTION_H

#include <ostream>

#define CURRENT_TYPE float



class Collection {
    int MAX, count;
    CURRENT_TYPE *data;
public:
    Collection();

    Collection(int n);

    ~Collection();

    bool isEmpty();

    //The Other Member Function:
    int insert_pos(CURRENT_TYPE what,int position);

    int insert_beginning(CURRENT_TYPE what);

    int insert_end(CURRENT_TYPE what);

    int insert_after(CURRENT_TYPE what, CURRENT_TYPE after_which);

    int insert_before(CURRENT_TYPE what, CURRENT_TYPE before_which);

    CURRENT_TYPE delete_beginning();

    CURRENT_TYPE delete_end();

    CURRENT_TYPE delete_pos(int position);

    CURRENT_TYPE delete_data(CURRENT_TYPE which);

    friend std::ostream &operator<<(std::ostream &os, const Collection &collection);
};


#endif //COLLECTION_H

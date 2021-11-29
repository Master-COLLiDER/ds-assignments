#ifndef COLLECTION_H
#define COLLECTION_H


#define CURRENT_TYPE float


class Collection {
    int MAX, count;
    CURRENT_TYPE *data;
public:
    Collection();

    Collection(int n);

    ~Collection();

    int getMax() const;

    bool isEmpty();

    int insert_pos(CURRENT_TYPE what, int position);

    int insert_beginning(CURRENT_TYPE what);

    int insert_end(CURRENT_TYPE what);

    int insert_after(CURRENT_TYPE what, CURRENT_TYPE after_which);

    int insert_before(CURRENT_TYPE what, CURRENT_TYPE before_which);

    CURRENT_TYPE delete_beginning();

    CURRENT_TYPE delete_end();

    CURRENT_TYPE delete_pos(int position);

    CURRENT_TYPE delete_data(CURRENT_TYPE which);

    int indexOf(CURRENT_TYPE which);

    void bubbleSort();

    void displayData();

};


#endif //COLLECTION_H

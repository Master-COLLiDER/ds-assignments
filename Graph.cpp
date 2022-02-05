#ifndef CSM21020_GRAPH_CPP
#define CSM21020_GRAPH_CPP

#include "Graph.h"
#include "node.h"

Graph::Graph(int n) {
    if (n < 1) {
        _node_count = 0;
        _node_label = NULL;
        _edges = NULL;
    } else {
        _node_label = (char *) malloc(sizeof(char) * n);
        if (_node_label == NULL) {
            _node_count = 0;
            _edges = NULL;
        } else {
            _edges = (Queue<graphEdge> *) malloc(n * sizeof(Queue<graphEdge>));
            if (_edges == NULL) {
                _node_count = 0;
                free(_node_label);
                _node_label = NULL;
            } else
                _node_count = n;
        }
    }
}    //End of parameterized Constructor



int Graph::set_edge(int from, int to, float wt) {
    queue_info_type data;
    qNode<int> temp;
    int status;
    if ((from < 0) || (from >= n))
        return 0;
    if ((to < 0) || (to >= n))
        return 0;
    if (from == to) //Simple graph
        return 0;
    if (wt <= 0) //positive weighted graph
        return 0;

    temp = edges[from].search(to); //searches for the "to" in the corresponding
    //field  of the info of queue _destination, if found
    //returns the address of the _destination,
    //if not found returns NULL
    if (temp != NULL)
        return 0;  //Edge from-to already exist
    data.dest = to;
    data._weight = wt;
    status = edges[from].enqueue(data);

    if (status == 1)
        return 1;
    return 0;
}


float graph::get_weight(int from, int to) {
    if ((from < 0) || (from >= n))
        return 0;
    if ((to < 0) || (to >= n))
        return 0;
    if (from == to) //Simple graph
        return 0;
    temp = edges[from]._front;
    while (temp != NULL) {
        if (temp.info.dest == to)
            return (temp.info._weight);
        temp = temp->ptr;
    }
    return 0;
}


int graph::set_label(int which, char *what) {
    char *cur;
    if (which < 0) && (which >= node_count)
    return 0; // invalid _destination
    if (strlen(what) > 19)
        what[19] = '\0'; //Labels are maximum 19 symbol long
    cur = _node_label + (20 * which);
    strcpy(cur, what);
    return 1;
}

int graph::show_label(int which) {
    char *cur;
    if (which < 0) && (which >= node_count)
    {
        print("invalid");
        return 0; // invalid _destination
    }
    cur = node_label + (20 * which);
    printf("%s", cur);
    return 1;
}


#endif //CSM21020_GRAPH_CPP


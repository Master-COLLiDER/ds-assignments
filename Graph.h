#ifndef GRAPH_H
#define GRAPH_H

#include "Queue.h"
#include <iostream>

struct graphEdge{
    int _destination;
    float _weight;
};

class Graph {
    unsigned _node_count;
    char *_node_label;
    Queue<graphEdge> *_edges;
public:
    //default constructor creates a NULL graph
    Graph() : _node_count(0), _node_label(NULL), _edges(NULL) {}

    //creates the vertices with provision to keep the outgoing edge
    Graph(int n);


    int set_edge(int from, int to, float wt = 1);

    float getWeight(int fromNode, int toNode);

    int out_degree(int which);
    //Todo: returns the count of outgoing _edges from a given _destination if valid, otherwise -1;

    int in_degree(int which);
    //Todo:  returns the count of incoming _edges from a given _destination if valid, otherwise -1;

    int show_outedges(int which);
    //Todo: Displays the (Node label and weight) for every outgoing _edges from the given _destination
    // and return 1 if valid _destination, returns 0 is invalid _destination

    int show_inedges(int which);
    //Todo: Displays the (Node label and weight) for every incoming _edges TO the given _destination
    // and return 1 if valid _destination, returns 0 is invalid _destination

    int set_label(int which, char *what);
    //Todo: For assigning the labels as per user's need

    char * get_label(int which);
    //Todo: For geting the label of a specified _destination, An empty string if _destination number is invalid



    int BFS(int start_pos = 0);
    //Todo: Display the BFS traversal of the graph from a specified _destination, if not specified from front _destination

    int DFS(int start_pos = 0);
    //Todo: Display the DFS traversal of the graph from a specified _destination, if not specified from front _destination

    int DFS_numbering();
    //Todo: Restructuring the graph representation by re-ording the nodes without loosing any information
    //Todo: Restructured graph should be stored in the same object, that has activated this function.


    PATH Shortest_Path(int from,
                       int to);
    //Todo: calculate the shortest path from the "from" _destination to all _destination, and sends the path intended path,
    // PATH is a finite (What??? hint. Longest path may have all the nodes) set of integers,
    // If no path exists, carinality of this set must be zero.


    graph MST_Prim();
    //Todo:  Finds a Minimal Spanning Tree for the graph using Prim's Algorithm,
    // A binary min-heap of _edges (a triples <from, to, Wt> ) maintained on Wt is needed for better efficiency.


    graph MST_Kruskal();
    //Todo:  Finds a Minimal Spanning Tree for the graph using Prim's Algorithm,
    // A binary min-heap of _edges (a triples <from, to, Wt> ) maintained on Wt is needed for better efficiency.
};


//Todo: All the operation below the marked position needs the support of some other _data structure.
// You need to implement those _data structure in a separate class.
// Information maintained in these _data structures may be different for different operation,
// need to design them carefully to avoid unnecessary duplicate codes.

#endif //GRAPH_H

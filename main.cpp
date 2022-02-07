/** Roll No. CSM21002 **/

#include <iostream>
#include <string.h>

#ifndef CSM21002_QUEUE_H
#define CSM21002_QUEUE_H
template<typename T>
struct qNode {
    T _data;
    qNode *_next;
    float _priority{0};
};

template<typename T>
class Queue {
    typedef qNode<T> *qnodeptr;
    qnodeptr _front, _rear;
public:
    Queue() : _front(NULL), _rear(NULL) {}

    ~Queue() {
        qnodeptr temp;
        _rear = NULL;
        while (_front != NULL) {
            temp = _front;
            _front = _front->_next;
            free(temp);
        }
    }

    bool enqueue(T data) {
        qnodeptr temp = (qnodeptr) malloc(sizeof(qNode<T>));
        if (!temp) {
            return false;
        }
        temp->_data = data;
        temp->_next = NULL;

        if (isEmpty()) {
            _front = _rear = temp;
        } else {
            _rear->_next = temp;
            _rear = temp;
        }
        return true;
    }

    //lower the value the higher is the priority
    bool priorityEnqueue(T data, float priority) {
        qnodeptr temp = (qnodeptr) malloc(sizeof(qNode<T>));
        if (!temp) {
            return false;
        }
        temp->_data = data;
        temp->_next = NULL;
        temp->_priority = priority;

        if (isEmpty()) {
            _front = _rear = temp;
        } else {

            if (_front->_priority >= priority) {
                temp->_next = _front;
                _front = temp;
            } else {
                qnodeptr tempnodeptr = _front;
                while (tempnodeptr->_next != NULL &&
                       tempnodeptr->_next->_priority < priority) {
                    tempnodeptr = tempnodeptr->_next;
                }
                temp->_next = tempnodeptr->_next;
                tempnodeptr->_next = temp;
                while (_rear->_next != NULL)
                    _rear = _rear->_next;
            }

        }
        return true;
    }

    float getFrontPriority() {
        if (isEmpty())
            return 0;
        return _front->_priority;
    }

    T dequeue() {
        qnodeptr temp;
        T toReturn;
        if (isEmpty()) {
            exit(1);
        }
        temp = _front;
        toReturn = temp->_data;
        if (_front == _rear)
            _rear = _rear->_next;
        _front = _front->_next;
        delete (temp);
        return toReturn;
    }


    qnodeptr front() {
        return _front;
    }

    bool isEmpty() {
        return _front == NULL;
    }
};

#endif //CSM21002_QUEUE_H


#ifndef CSM21002_GRAPH_H
#define CSM21002_GRAPH_H
struct graphEdge {
    int _destination;
    float _weight;
};

struct PATH {
    float cost{};
    int prev{};
};

class Graph {
    int _node_count;
    char **_node_label;
    Queue<graphEdge> *_edges;


    qNode<graphEdge> *searchEdge(int fromNode, int toNode) {
        qNode<graphEdge> *temp = _edges[fromNode].front();

        while (temp != NULL) {
            if (temp->_data._destination == toNode)
                return temp;
            temp = temp->_next;
        }
        return NULL;
    }

    //Used to check if the edge exits
    bool hasTheEdge(int fromNode, int toNode) {
        return searchEdge(fromNode, toNode) != NULL;
    }


    bool isValidVertex(int nodeNumber) {
        if ((nodeNumber < 0) || (nodeNumber >= _node_count))
            return false;
        return true;
    }


public:
    Graph() : _node_count(0), _node_label(NULL), _edges(NULL) {}

    //destructor of graph class
    //
    ~Graph() {
        int i;
        for (i = 0; i < _node_count; i++) {
            free(_node_label[i]);
        }
        free(_node_label);
        free(_edges);
    }

    //graph constructor funciton
    Graph(int n) {
        if (n < 1) {
            _node_count = 0;
            _node_label = NULL;
            _edges = NULL;
        } else {
            //pointer to char pointer is allocated with n number of char*
            _node_label = (char **) malloc(sizeof(char *) * n);
            if (_node_label == NULL) {
                _node_count = 0;
                _edges = NULL;
            } else {
                int i;

                //for each char * in _node_labels char** a char array of size 20 is allocated;
                for (i = 0; i < n; i++) {
                    _node_label[i] = (char *) malloc(sizeof(char) * 20);
                    strcpy(_node_label[i], "No Label");
                }
                //_edges is allocaed with an array of Queue<graphEdge> of n size;
                ///Note: using of malloc() does not call constructor Therefore queue is not initialized
                ///i dont know why but my code only works on linux
                ///On windows it exits when calling member functions of Queue class;
                _edges = (Queue<graphEdge> *) malloc(n * sizeof(Queue<graphEdge>));
                if (_edges == NULL) {
                    _node_count = 0;
                    //if graphEdge queue allocation is failed, each char * in label is deallocated
                    for (i = 0; i < n; i++) {
                        free(_node_label[i]);
                    }
                    free(_node_label);

                    _node_label = NULL;
                } else
                    _node_count = n;
            }
        }
    }


    //This function is used to used to set edge
    //Return a boolean value
    //if invalid vertex is given then it return false
    //it return the status return by the Queue::enqueue() function
    bool setEdge(int fromNode, int toNode, float weight) {
        if (!isValidVertex(fromNode))
            return false;
        if (!isValidVertex(toNode))
            return false;
        if (fromNode == toNode) //Simple graph
            return false;
        if (weight <= 0) //positive weighted graph
            return false;

        if (hasTheEdge(fromNode, toNode))
            return false;  //Edge fromNode-toNode already exist

        graphEdge data{};
        data._destination = toNode;
        data._weight = weight;
        return _edges[fromNode].enqueue(data);
    }

    //This function returns the weight for a given edge if edge is available in queue of _edges[source vertex]
    //Returns 0 if edge is not found
    float getWeight(int fromNode, int toNode) {
        if (!isValidVertex(fromNode))
            return 0;
        if (!isValidVertex(toNode))
            return 0;
        if (fromNode == toNode) //Simple graph
            return 0;
        qNode<graphEdge> *temp = _edges[fromNode].front();
        while (temp != NULL) {
            if (temp->_data._destination == toNode)
                return (temp->_data._weight);
            temp = temp->_next;
        }
        return 0;
    }

    //returns the outgoing edges for a given vertex
    int outDegree(int nodeNumber) {
        int degree = 0;
        if (!isValidVertex(nodeNumber))
            return degree;
        qNode<graphEdge> *temp = _edges[nodeNumber].front();
        while (temp != NULL) {
            degree++;
            temp = temp->_next;
        }
        return degree;
    }

    // Return the number of incoming edges for the given vertex
    int inDegree(int nodeNumber) {
        int degree = 0, i;
        if (!isValidVertex(nodeNumber))
            return degree;
        for (i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            if (hasTheEdge(i, nodeNumber))
                degree++;
        }
        return degree;
    }

    // sets label in _node_label char array;
    bool setLabel(int nodeNumber, char *labelText) {
        if (!isValidVertex(nodeNumber))
            return false; // invalid _destination
        if (strlen(labelText) > 19)
            labelText[19] = '\0'; //Labels are maximum 19 symbol long
        strcpy(_node_label[nodeNumber], labelText);
        return true;
    }

    //Mapping function to convert label to vertex
    int labelToVertex(char *labelText) {
        int v;
        for (v = (_node_count - 1); v > -1; v--) {
            if (strcmp(labelText, _node_label[v]) == 0)
                return v;
        }
        return v; // return -1 if no matching vertex is found of given label
    }

    const char *getLabel(int nodeNumber) {

        if (!isValidVertex(nodeNumber)) {
            return NULL; // invalid _destination
        }
        return _node_label[nodeNumber];
    }

    //Displays outgoing edges for a given vertex
    int showOutEdges(int nodeNumber) {
        if (!isValidVertex(nodeNumber))
            return 0;
        qNode<graphEdge> *temp = _edges[nodeNumber].front();

        printf("Out Edges from node %s ---> ", getLabel(nodeNumber));
        while (temp != NULL) {
            printf("\n(%s , Weight: %f ),", getLabel(temp->_data._destination), temp->_data._weight);
            temp = temp->_next;
        }
        return 1;
    }

    //Displays Incoming edges for a vertex
    int showInEdges(int nodeNumber) {
        if (!isValidVertex(nodeNumber))
            return 0;
        qNode<graphEdge> *temp;
        int i;
        printf("In Edges to node  %s <--- ", getLabel(nodeNumber));
        for (i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            temp = searchEdge(i, nodeNumber);
            if (temp != NULL)
                printf("\n(%s , Weight: %f ),", getLabel(i),
                       temp->_data._weight);
        }
        return 1;
    }
    //The shortest path function is finds the shortest path between two vertex
    //if given vertex are vaid,
    //Allocates an array of PATH structure and retruns that after processing
    PATH *ShortestPath(int sourceNode, int destinationNode) {
        if (!isValidVertex(sourceNode))
            return NULL;
        if (!isValidVertex(destinationNode))
            return NULL;
        PATH *path = (PATH *) malloc(sizeof(PATH) * _node_count);
        if (path == NULL)
            return path;
        struct graphEdgeWithoutWeight {
            int fromNode;
            int toNode;
        };
        float cost;
        graphEdgeWithoutWeight tempEdge{};
        int cNode, pNode, i;

        Queue<graphEdgeWithoutWeight> pQueue;

        for (i = 0; i < _node_count; ++i) {
            path[i].prev = -1;
            path[i].cost = 0;
        }

        qNode<graphEdge> *tempQNodeptr = _edges[sourceNode].front();
        while (tempQNodeptr != NULL) {
            graphEdgeWithoutWeight tEdge{};
            tEdge.fromNode = sourceNode;
            tEdge.toNode = tempQNodeptr->_data._destination;
            pQueue.priorityEnqueue(tEdge, tempQNodeptr->_data._weight);
            tempQNodeptr = tempQNodeptr->_next;
        }
        while (!pQueue.isEmpty()) {
            cost = pQueue.getFrontPriority();
            tempEdge = pQueue.dequeue();
            cNode = tempEdge.toNode;
            pNode = tempEdge.fromNode;

            if (((path[cNode].prev == -1) || (path[cNode].cost > cost)) && cNode != sourceNode) {
                path[cNode].cost = cost;
                path[cNode].prev = pNode;
                tempQNodeptr = _edges[cNode].front();
                while (tempQNodeptr != NULL) {
                    graphEdgeWithoutWeight tEdge{};
                    tEdge.fromNode = cNode;
                    tEdge.toNode = tempQNodeptr->_data._destination;
                    pQueue.priorityEnqueue(tEdge, tempQNodeptr->_data._weight + cost);
                    tempQNodeptr = tempQNodeptr->_next;
                }
            }

        }
        return path;
    }

    //this function is used to find bfs traversal the outputqueue is used to enqueue the resulted vertex
    //results 1 if success 0 invalid start vertex is given
    int BFS_Traversal(Queue<int> &outputQueue, int startNode = 0) {
        if (!isValidVertex(startNode))
            return 0;
        Queue<int> queue;
        int i, v;
        bool visited[_node_count];
        for (i = 0; i < _node_count; ++i) {
            visited[i] = false;
        }
        visited[startNode] = true;
        queue.enqueue(startNode);
        qNode<graphEdge> *temp;
        while (!queue.isEmpty()) {
            v = queue.dequeue();
            outputQueue.enqueue(v);
            temp = _edges[v].front();
            while (temp != NULL) {
                if (!visited[temp->_data._destination]) {
                    visited[temp->_data._destination] = true;
                    queue.enqueue(temp->_data._destination);
                }
                temp = temp->_next;
            }
        }
        return 1;
    }

    //displays shortest between two nodes after calling ShortestPath function
    void showShortestPath(int sourceNode, int destinationNode) {
        int i;
        PATH *path = ShortestPath(sourceNode, destinationNode);

        if (path == NULL)
            printf("\n Failed to find any path!");
        else {
            printf("\n Vertex | Previous Vertex  | Cost to Reach");
            for (i = 0; i < _node_count; ++i) {
                printf("\n %s | %s  | %f", getLabel(i), (path[i].prev == -1 ? "N/A" : getLabel(path[i].prev)),
                       path[i].cost);

            }
            if (path[destinationNode].prev == -1)
                printf("\n No route found! between %s and %s", getLabel(sourceNode), getLabel(destinationNode));
            else {
                printf("\n Shortest Path to vertex %s from vertex %s :\n", getLabel(destinationNode),
                       getLabel(sourceNode));
                for (i = destinationNode; i != sourceNode;) {
                    printf("%s <- ", getLabel(i));
                    i = path[i].prev;
                }
                printf("%s | Total Cost : %f", getLabel(sourceNode), path[destinationNode].cost);
            }
            free(path);
        }

    }

    //Displays BFS traversal results after calling the bfs traversal fucniton
    int show_BFS_Traversal(int startNode = 0) {
        if (!isValidVertex(startNode)) {
            std::cout << "\nInvalid Vertex";
            return 0;
        }
        printf("BFS traversal FROM node %s ---> ", getLabel(startNode));
        Queue<int> queue;
        if (BFS_Traversal(queue, startNode = startNode))
            while (!queue.isEmpty()) {
                printf("%s, ", getLabel(queue.dequeue()));
            }
        return 1;
    }


};

#endif //CSM21002_GRAPH_H


int main() {

    char text1[40], text2[40];
    char choice;
    int n, i;
    float wt;
    std::cout << "\nEnter the number of vertex in the graph: ";
    std::cin >> n;
    Graph graph(n);

    for (i = 0; i < n; i++) {
        std::cout << "\nEnter Label for Vertex " << i + 1 << " : ";
        std::cin >> text1;
        graph.setLabel(i, text1);
    }
    while (true) {
        std::cout << "\nRoll No. : CSM21002";
        std::cout << "\n::: Graph MainMenu:::";
        std::cout
                << "\n1. Set Edge\n2. Shortest Path\n3. BFS Traversal\n4. Show Incoming Edges\n5. Show Outgoing Edges\nE. Exit\n\n Enter Your Choice: ";
        std::cin >> choice;
        switch (choice) {
            case '1': {
                std::cout << "\nEnter the label of source vertex for the edge: ";
                std::cin >> text1;
                std::cout << "\nEnter the label of destination vertex for the edge: ";
                std::cin >> text2;
                std::cout << "\nEnter the weight edge: ";
                std::cin >> wt;
                if (graph.setEdge(graph.labelToVertex(text1), graph.labelToVertex(text2), wt))
                    printf("\nSuccessfully Set edge (%s, %s, %f ) ", text1, text2, wt);
                else
                    std::cout << "\nFailed to set edge ";
                std::cin.get();
                break;
            }
            case '2': {
                std::cout << "\nEnter the label of source vertex: ";
                std::cin >> text1;
                std::cout << "\nEnter the label of destination vertex: ";
                std::cin >> text2;
                graph.showShortestPath(graph.labelToVertex(text1), graph.labelToVertex(text2));
                std::cin.get();
                break;
            }
            case '3': {
                std::cout << "\nEnter the label of starting vertex for BFS traversal: ";
                std::cin >> text1;
                if (!graph.show_BFS_Traversal(graph.labelToVertex(text1)))
                    std::cout << "\nTraversal failed! ";
                std::cin.get();
                break;
            }
            case '4': {
                std::cout << "\nEnter the Vertex label: ";
                std::cin >> text1;
                printf("\nIn degree of %s : %d\n", text1, graph.inDegree(graph.labelToVertex(text1)));
                graph.showInEdges(graph.labelToVertex(text1));
                std::cin.get();
                break;
            }
            case '5': {
                std::cout << "\nEnter the Vertex label: ";
                std::cin >> text1;
                printf("\nOut degree of %s : %d\n", text1, graph.outDegree(graph.labelToVertex(text1)));
                graph.showOutEdges(graph.labelToVertex(text1));
                std::cin.get();
                break;
            }

            case 'E':
            case 'e':
                return 0;

            default: {
                std::cout << "\nInvalid Choice!";
                std::cin.get();
                break;
            }
        }
    }
}

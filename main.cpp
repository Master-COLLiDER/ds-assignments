#include <iostream>
#include <cstring>

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
        if (_front == NULL) {
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
    float cost{-1};
    int prev{0};
};

class Graph {
    unsigned _node_count;
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

    bool hasTheEdge(int fromNode, int toNode) {
        return searchEdge(fromNode, toNode) != NULL;
    }


    bool isValidNode(int nodeNumber) {
        if ((nodeNumber < 0) || (nodeNumber >= _node_count))
            return false;
        return true;
    }


public:
    Graph() : _node_count(0), _node_label(NULL), _edges(NULL) {}

    ~Graph() {
        int i;
        for (i = 0; i < _node_count; i++) {
            free(_node_label[i]);
        }
        free(_node_label);
        free(_edges);
    }

    Graph(int n) {
        if (n < 1) {
            _node_count = 0;
            _node_label = NULL;
            _edges = NULL;
        } else {
            _node_label = (char **) malloc(sizeof(char *) * n);
            if (_node_label == NULL) {
                _node_count = 0;
                _edges = NULL;
            } else {
                int i;
                for (i = 0; i < n; i++) {
                    _node_label[i] = (char *) malloc(sizeof(char) * 20);
                    strcpy(_node_label[i], "No Label");
                }
                _edges = (Queue<graphEdge> *) malloc(n * sizeof(Queue<graphEdge>));
                if (_edges == NULL) {
                    _node_count = 0;
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


    bool setEdge(int fromNode, int toNode, float weight) {
        if (!isValidNode(fromNode))
            return false;
        if (!isValidNode(toNode))
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

    float getWeight(int fromNode, int toNode) {
        if (!isValidNode(fromNode))
            return 0;
        if (!isValidNode(toNode))
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


    int outDegree(int nodeNumber) {
        int degree = 0;
        if (!isValidNode(nodeNumber))
            return degree;
        qNode<graphEdge> *temp = _edges[nodeNumber].front();
        while (temp != NULL) {
            degree++;
            temp = temp->_next;
        }
        return degree;
    }

    int inDegree(int nodeNumber) {
        int degree = 0, i;
        if (!isValidNode(nodeNumber))
            return degree;
        for (i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            if (hasTheEdge(i, nodeNumber))
                degree++;
        }
        return degree;
    }

    bool setLabel(int nodeNumber, char *labelText) {
        if (!isValidNode(nodeNumber))
            return false; // invalid _destination
        if (strlen(labelText) > 19)
            labelText[19] = '\0'; //Labels are maximum 19 symbol long
        strcpy(_node_label[nodeNumber], labelText);
        return true;
    }

    int labelToVertex(char *labelText) {
        int i;
        for (i = (_node_count - 1); i > -1; i--) {

            if (strcmp(labelText, _node_label[i]) == 0)
                return i;
        }
        return i;
    }

    char *getLabel(int nodeNumber) {
        char *cur;
        if (!isValidNode(nodeNumber)) {
            return NULL; // invalid _destination
        } else {
            cur = strdup(_node_label[nodeNumber]);
        }
        return cur;
    }


    int showOutEdges(int nodeNumber) {
        if (!isValidNode(nodeNumber))
            return 0;
        qNode<graphEdge> *temp = _edges[nodeNumber].front();

        printf("Out Edges from node %s ---> ", getLabel(nodeNumber));
        while (temp != NULL) {
            printf("\n(%s , Weight: %f ),", getLabel(temp->_data._destination), temp->_data._weight);
            temp = temp->_next;
        }
        return 1;
    }

    int showInEdges(int nodeNumber) {
        if (!isValidNode(nodeNumber))
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

    int BFS_Traversal(int startNode = 0) {
        if (!isValidNode(startNode))
            return 0;
        printf("BFS traversal FROM node %s ---> ", getLabel(startNode));
        Queue<int> queue;
        int i;
        bool visited[_node_count];
        for (i = 0; i < _node_count; ++i) {
            visited[i] = false;
        }
        visited[startNode] = true;
        queue.enqueue(startNode);
        qNode<graphEdge> *temp;
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            printf("%s, ", getLabel(v));
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


    PATH *ShortestPath(int sourceNode, int destinationNode) {
        if (!isValidNode(sourceNode))
            return NULL;
        if (!isValidNode(destinationNode))
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
                printf("\n No route found! between %S and %S", getLabel(sourceNode), getLabel(destinationNode));
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

};

#endif //CSM21002_GRAPH_H


int main() {

    char label[20], e1[20], e2[20];
    char choice;
    int n, i;
    float wt;
    std::cout << "\nEnter the number of vertex in the graph: ";
    std::cin >> n;
    Graph graph(n);

    for (i = 0; i < n; i++) {
        std::cout << "\nEnter Label for Vertex " << i + 1 << " : ";
        std::cin >> label;
        graph.setLabel(i, label);
    }
    while (true) {
        std::cout << "\nRoll No. : CSM21002";
        std::cout << "\n::: Graph MainMenu:::";
        std::cout
                << "\n1. Set Edge\n2. Shortest Path\n3. BFS Traversal\n4. Show Incoming Edges\n5. Show Outgoing Edges\nE. Exit\n\n Enter Your Choice: ";
        std::cin >> choice;
        switch (choice) {
            case '1': {
//                graph.setEdge(0,1,5);
//                graph.setEdge(1,2,6);
//                graph.setEdge(1,3,5);
//                graph.setEdge(2,0,13);
//                graph.setEdge(2,4,1);
//                graph.setEdge(3,4,3);
                std::cout << "\nEnter the label of source vertex for the edge: ";
                std::cin >> e1;
                std::cout << "\nEnter the label of destination vertex for the edge: ";
                std::cin >> e2;
                std::cout << "\nEnter the weight edge: ";
                std::cin >> wt;
                if (graph.setEdge(graph.labelToVertex(e1), graph.labelToVertex(e2), wt))
                    printf("\nSuccessfully Set edge (%s, %s, %f ) ", e1, e2, wt);
                else
                    std::cout << "\nFailed to set edge ";
                std::cin.get();
                break;
            }
            case '2': {
                std::cout << "\nEnter the label of source vertex: ";
                std::cin >> e1;
                std::cout << "\nEnter the label of destination vertex: ";
                std::cin >> e2;
                graph.showShortestPath(graph.labelToVertex(e1), graph.labelToVertex(e2));
                std::cin.get();
                break;
            }
            case '3': {
                std::cout << "\nEnter the label of starting vertex for BFS traversal: ";
                std::cin >> e1;
                if (!graph.BFS_Traversal(graph.labelToVertex(e1)))
                    std::cout << "\nTraversal failed! ";
                std::cin.get();
                break;
            }
            case '4': {
                std::cout << "\nEnter the Vertex label: ";
                std::cin >> e1;
                printf("\nIn degree of %s : %d\n",e1,graph.inDegree(graph.labelToVertex(e1)));
                graph.showInEdges(graph.labelToVertex(e1));
                std::cin.get();
                break;
            }
            case '5': {
                std::cout << "\nEnter the Vertex label: ";
                std::cin >> e1;
                printf("\nOut degree of %s : %d\n",e1,graph.outDegree(graph.labelToVertex(e1)));
                graph.showOutEdges(graph.labelToVertex(e1));
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


    return 0;
}

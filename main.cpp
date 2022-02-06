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
                while (_rear->_next!=NULL)
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
        qNode<graphEdge>* temp = _edges[fromNode].front();

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
                    strcpy(_node_label[i],  "No Label");
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
        qNode<graphEdge>* temp = _edges[nodeNumber].front();

        printf("Out Edges from node %d: %s ---> ", nodeNumber, getLabel(nodeNumber));
        while (temp != NULL) {
            printf("\n( %d: %s , Weight: %f ),", temp->_data._destination, getLabel(temp->_data._destination),
                   temp->_data._weight);
            temp = temp->_next;
        }
        return 1;
    }

    int showInEdges(int nodeNumber) {
        if (!isValidNode(nodeNumber))
            return 0;
        qNode<graphEdge>* temp;
        int i;
        printf("In Edges to node %d: %s <--- ", nodeNumber, getLabel(nodeNumber));
        for (i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            temp = searchEdge(i, nodeNumber);
            if (temp != NULL)
                printf("\n( %d: %s , Weight: %f ),", i, getLabel(i),
                       temp->_data._weight);
        }
        return 1;
    }

    int BFS_Traversal(int startNode = 0) {
        if (!isValidNode(startNode))
            return 0;
        printf("BFS traversal from node 1 ---> ", startNode, getLabel(startNode));
        Queue<int> queue;
        int i;
        bool visited[_node_count];
        for (i = 0; i < _node_count; ++i) {
            visited[i] = false;
        }
        visited[startNode] = true;
        queue.enqueue(startNode);
        qNode<graphEdge>* temp;
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            printf(" ( %d: %s ),", v, getLabel(v));
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

        printf("\n Failed to find any path!");
        if (path != NULL) {
            printf("\n Node | Prev  | Cost");
            for (i = 0; i < _node_count; ++i) {
                if (i == sourceNode)
                    continue;
                printf("\n %d | %d  | %f", i, path[i].prev, path[i].cost);

            }
            if (path[destinationNode].prev == -1)
                printf("\n No route found! between %d and %d",sourceNode,destinationNode);
            else {
                printf("\n Shortest Path to %d from %d :\n", destinationNode, sourceNode);
                for (i = destinationNode; i != sourceNode;) {
                    printf("%d <- ", i);
                    i = path[i].prev;
                }
                printf("%d | Cost : %f", sourceNode, path[destinationNode].cost);
            }
            free(path);
        }

    }

};

#endif //CSM21002_GRAPH_H


int main() {

    return 0;
}

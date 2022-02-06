#include <iostream>
#include <cstring>

#ifndef CSM21002_QUEUE_H
#define CSM21002_QUEUE_H
template<typename T>
struct qNode {
    T _data{NULL};
    qNode *_next{NULL};
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
        auto temp = (qnodeptr) malloc(sizeof(qNode<T>));
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

    bool priorityEnqueue(T data, float priority) {
        auto temp = (qnodeptr) malloc(sizeof(qNode<T>));
        if (!temp) {
            return false;
        }
        temp->_data = data;
        temp->_next = NULL;
        temp->_priority = priority;

        if (isEmpty()) {
            _front = _rear = temp;
        } else {

            if (_front->_priority > priority) {
                temp->_next = _front;
                _front = temp;
            } else {
                auto tempnodeptr = _front;
                while (tempnodeptr->_next != NULL &&
                       tempnodeptr->_next->_priority < priority) {
                    tempnodeptr = tempnodeptr->_next;
                }

                temp->_next = tempnodeptr->_next;
                temp->_next = temp;
            }

        }
        return true;
    }
    float getFrontPriority(){
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

class Graph {
    unsigned _node_count;
    char **_node_label;
    Queue<graphEdge> *_edges;
public:
    Graph() : _node_count(0), _node_label(NULL), _edges(NULL) {}

    ~Graph() {
        for (int i = 0; i < _node_count; i++) {
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
                for (int i = 0; i < n; i++) {
                    _node_label[i] = (char *) malloc(sizeof(char) * 20);
                    char cur[20] = "No Label";
                    strcpy(_node_label[i], cur);
                }
                _edges = (Queue<graphEdge> *) malloc(n * sizeof(Queue<graphEdge>));
                if (_edges == NULL) {
                    _node_count = 0;
                    for (int i = 0; i < n; i++) {
                        free(_node_label[i]);
                    }
                    free(_node_label);

                    _node_label = NULL;
                } else
                    _node_count = n;
            }
        }
    }

    qNode<graphEdge> *searchEdge(int fromNode, int toNode) {
        auto temp = _edges[fromNode].front();

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

    bool setEdge(int fromNode, int toNode, float weight) {
        graphEdge data;
        int status;
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
        auto temp = _edges[fromNode].front();
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
        auto temp = _edges[nodeNumber].front();
        while (temp != NULL) {
            degree++;
            temp = temp->_next;
        }
        return degree;
    }

    int inDegree(int nodeNumber) {
        int degree = 0;
        if (!isValidNode(nodeNumber))
            return degree;
        for (int i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            if (hasTheEdge(i, nodeNumber))
                degree++;
        }
        return degree;
    }

    bool setLabel(int nodeNumber, char *labelText) {
        char *cur;
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
        auto temp = _edges[nodeNumber].front();

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
        printf("In Edges to node %d: %s <--- ", nodeNumber, getLabel(nodeNumber));
        for (int i = 0; i < _node_count; ++i) {
            if (i == nodeNumber)
                continue;
            auto temp = searchEdge(i, nodeNumber);
            if (temp != NULL)
                printf("\n( %d: %s , Weight: %f ),", i, getLabel(i),
                       temp->_data._weight);
        }
        return 1;
    }

    int breadthFirstSearch(int startNode = 0) {
        if (!isValidNode(startNode))
            return 0;
        printf("BFS traversal from node 1 ---> ", startNode, getLabel(startNode));
        Queue<int> queue;
        bool visited[_node_count];
        for (int i = 0; i < _node_count; ++i) {
            visited[i] = false;
        }
        visited[startNode] = true;
        queue.enqueue(startNode);
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            printf(" ( %d: %s ),", v, getLabel(v));
            auto temp = _edges[v].front();
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

    qNode<graphEdge> *shortestPath(int sourceNode, int destinationNode) {
        if (!isValidNode(sourceNode))
            return  NULL;
        if (!isValidNode(destinationNode))
            return  NULL;

        float cost[_node_count];
        int prev[_node_count];
        struct graphPQEdge{
            int from;
            int to;
        };
        Queue<graphPQEdge> Q;
        for (int v = 0; v < _node_count; ++v) {
            cost[v] =  0;
            prev[v] = -1;
        }
//        distance[sourceNode] = 0;
//        while(!q.empty()){
//
//        }
//        12          u ← vertex in Q with min dist[u]
//        13
//        14          remove u sourceNode Q
//        15
//        16          for each neighbor v of u still in Q:
//        17              alt ← dist[u] + Graph.Edges(u, v)
//        18              if alt < dist[v]:
//        19                  dist[v] ← alt
//        20                  prev[v] ← u
//        21
//        22      return dist[], prev[]
        return NULL;
    }

};

#endif //CSM21002_GRAPH_H


int main() {

    Graph g1(10);
    g1.setEdge(1, 2, 34);
    g1.setEdge(1, 3, 3.1);
    g1.setEdge(2, 1, 2.1);
    g1.setEdge(3, 9, 2.1);
    g1.setLabel(1, "Mumbai");
    g1.setLabel(2, "Kolkata");
    g1.setLabel(3, "Chennai");
//    g1.breadthFirstSearch(-1);
//    g1.breadthFirstSearch(1);
    g1.showOutEdges(1);

    return 0;
}

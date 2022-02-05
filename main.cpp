#include <iostream>
#include <cstring>

#ifndef CSM21002_QUEUE_H
#define CSM21002_QUEUE_H
template<typename T>
struct qNode {
    T _data{NULL};
    qNode *_next{NULL};
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


    bool hasTheEdge(int fromNode, int toNode) {
        auto temp = _edges[fromNode].front();

        while (temp != NULL) {
            if (temp->_data._destination == toNode)
                return true;
            temp = temp->_next;
        }
        return false;
    }

    bool setEdge(int fromNode, int toNode, float weight) {
        graphEdge data;
        int status;
        if ((fromNode < 0) || (fromNode >= _node_count))
            return false;
        if ((toNode < 0) || (toNode >= _node_count))
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
        if ((fromNode < 0) || (fromNode >= _node_count))
            return 0;
        if ((toNode < 0) || (toNode >= _node_count))
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
        if ((nodeNumber >= _node_count) || (nodeNumber < 0))
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
        if ((nodeNumber >= _node_count) || (nodeNumber < 0))
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
        if ((nodeNumber < 0) || (nodeNumber >= _node_count))
            return false; // invalid _destination
        if (strlen(labelText) > 19)
            labelText[19] = '\0'; //Labels are maximum 19 symbol long

        strcpy(_node_label[nodeNumber], labelText);
        return 1;
    }

};

#endif //CSM21002_GRAPH_H


int main() {

    Graph g1(10);
    g1.setEdge(1, 2, 34);
    g1.setEdge(1, 3, 3.1);
    g1.setEdge(2, 1, 2.1);

    std::cout << "outDegree 1 : " << g1.outDegree(1);
    return 0;
}

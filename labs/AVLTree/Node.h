#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
        int counter;
        string data;
        Node *parent;
        Node *right;
        Node *left;
        Node(string data, int counter): counter(counter), data(data), parent(0), right(0), left(0) {} 
};

#endif
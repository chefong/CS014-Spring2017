#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

struct Node{
    string data;
    int balanceNum;
    Node* left;
    Node* right;
    Node* parent;
    Node(string data) : data(data), balanceNum(0), left(0), right(0), parent(0) {}
};
class AVLTree{
    private:
        Node* root;

    public:
        AVLTree() : root(0) {};
        void insert(const string &);
        int balanceFactor(Node *);
        void printBalanceFactors(); 
        void visualizeTree(const string &);

    private:
        int height(Node *);
        Node* findUnbalancedNode(Node *);
        void rotate(Node *);
        Node* rotateLeft(Node *);
        Node* rotateRight(Node *);
        void printBalanceFactors(Node *);
        void visualizeTree(ofstream &, Node *);
        void rebalance(Node *);
        bool search(const string&) const;
};

#endif
#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

struct Node {
    string word;
    int counter;
    Node *parent;
    Node *right;
    Node *left;
    Node(string word, int counter): word(word), counter(counter), parent(0), right(0), left(0) {} 
};

class BSTree {

  private:
    Node *root;

  private:
    void inOrder(Node *) const;
    void postOrder(Node *) const;
    void preOrder(Node *) const;
    void remove(Node *, const string &);
    Node* search(Node *, const string &) const;
    int height(Node *) const;
    Node* leftMax(Node *);
    Node* rightMin(Node *);

  public:
    BSTree() : root(0) {}
    void insert(const string &);
    bool search(const string &) const;
    void inOrder() const;
    void postOrder() const;
    void preOrder() const;
    string largest() const;
    string smallest() const;
    int height(const string &) const;
    void remove(const string &);
};

#endif
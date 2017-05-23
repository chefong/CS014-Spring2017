#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

  public:

    //constructs a node and assigns string to small.
    Node(const string &);

  private:
    string small;
    string large;

    Node *left;
    Node *middle;
    Node *right;
    Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif

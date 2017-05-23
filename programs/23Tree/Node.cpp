#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(const string & title) : small(title), left(0), middle(0), right(0), parent(0) {}
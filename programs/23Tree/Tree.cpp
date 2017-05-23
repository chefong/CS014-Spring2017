#include "Tree.h"
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

Tree::~Tree() {
    deleteNodes(root);
}

bool Tree::isLeafNode(Node *current) const {
    if (current->left == 0 && current->middle == 0 && current->right == 0) {
        return true;
    }
    return false;
}

bool Tree::is2Node(Node *current) const {
    if (current->large.empty()) { //is 2 Node if large is empty
        return true;
    }
    return false;
}

bool Tree::is3Node(Node *current) const {
    if (!current->small.empty() && !current->large.empty()) { //is 3 Node if BOTH small and large data exist
        return true;
    }
    return false;
}

void Tree::preOrder(Node *current) const {
    if (current) {
        cout << current->small << ", ";
        preOrder(current->left);
        if (is3Node(current)) {
            cout << current->large << ", ";
            preOrder(current->middle);
        }
        preOrder(current->right);
    }
}

void Tree::preOrder() const {
    preOrder(root); //calls recursive preOrder starting at the root.
}

void Tree::inOrder(Node *current) const {
    if (current) {
        inOrder(current->left);
        cout << current->small << ", ";
        if(is3Node(current)){
            inOrder(current->middle);
            cout << current->large << ", ";
        }
        inOrder(current->right);
    }
}

void Tree::inOrder() const {
    inOrder(root); //calls recursive inOrder starting at the root.
}

void Tree::postOrder(Node *current) const {
    if (current) {
        postOrder(current ->left);
        if (is3Node(current)) {
            postOrder(current->middle);
            cout << current->small << ", ";
        }
        postOrder(current -> right);
        if (is2Node(current)) {
            cout << current->small << ", ";
        }
        if (is3Node(current)) {
            cout << current->large << ", ";
        }
    }
}

void Tree::postOrder() const {
    postOrder(root); //calls recursive postOrder starting at the root.
}

Node* Tree::search(Node *current, const string & userWord) const {
    if (current) {
        if(isLeafNode(current)) {
            return current;
        }
        else if(is2Node(current)) {
            if(userWord == current->small || userWord == current->large) {
                return current;
            }
            else if(userWord < current->small) {
                return search(current->left, userWord);
            }
            else {
                return search(current->right, userWord);
            }
        }
        else {
            if(userWord == current->small || userWord == current->large) { 
                return current;
            }
            else if(userWord < current->small) {
                return search(current->left, userWord);
            }
            else if(userWord > current->large) {
                return search(current->right, userWord);
            }
            else {
                return search(current->middle, userWord);
            }
        }
   }
   return 0;
    //     if (current->small == userWord || current->large == userWord) { //return Node pointer if small or large match
    //         return current;
    //     }
    //     else {
    //         if (userWord < current->small) { //searches down left subtree
    //             return search(current->left, userWord);
    //         }
    //         else if (userWord < current->large) { //searches down middle subtree
    //             return search(current->middle, userWord);
    //         }
    //         else {
    //             return search(current->right, userWord); //searches down right subtree
    //         }
    //     }
    // }
    // return 0;
}

bool Tree::search(const string & userWord) const {
    Node *match = search(root, userWord); //assigns a Node pointer to the Node pointer returned from searching
    if (match->small == userWord || match->large == userWord) {
        return true;
    }
    return false;
}

string Tree::smallString(Node *current, const string & userWord) {
    string smallWord;
    if (userWord < current->small) {
        smallWord = userWord;
    }
    else {
        smallWord = current->small;
    }
    return smallWord;
}

string Tree::middleString(Node *current, const string & userWord) {
    string middleWord;
    if (userWord < current->small) {
        middleWord = current->small;
    }
    else if (userWord < current->large) {
        middleWord = userWord;
    }
    else {
        middleWord = current->large;
    }
    return middleWord;
}

string Tree::largeString(Node *current, const string & userWord) {
    string largeWord;
    if (userWord < current->large) {
        largeWord = current->large;
    }
    else {
        largeWord = userWord;
    }
    return largeWord;
}

void Tree::insert(const string & userWord) {
    Node *current = root;

    if (root == 0) {
        root = new Node(userWord);
        return;
    }

    //locates the leaf node of where to insert
    while (current->left != 0 || current->right != 0) {
        if (userWord < current->small) {
            current = current->left;
        }
        else if (userWord > current->large) {
            current = current->right;
        }
        else {
            if (current->middle != 0) {
                current = current->middle;
            }
        }
    }

    if (is2Node(current)) {
        if (userWord < current->small) {
            current->large = current->small;
            current->small = userWord;
        }
        else {
            current->large = userWord;
        }
    }
    else {
        // cout << "splitting with " << userWord << endl;
        split(current, userWord, 0, 0, 0, 0);
    }
}

void Tree::split(Node *n, const string & userWord, Node *left1, Node *left2, Node *right1, Node *right2) {
   string smallVal = smallString(n, userWord);
   string midVal = middleString(n, userWord);
   string largeVal = largeString(n, userWord);
   Node *p = 0;
   Node *child1 = 0;
   Node *child2 = 0;
   Node *child3 = 0;
   Node *child4 = 0;

   if(n == root) {
      p = new Node(midVal);
   }
   else {   
      p = n->parent;
   }
   
   Node *n1 = new Node(smallVal); // small
   Node *n2 = new Node(largeVal); //large

   n1->parent = p; 
   n2->parent = p; 
      
   //case if not a leaf node
   if (!isLeafNode(n)) {
      //assign n1 as parent of n's two leftmost children
      left1->parent = n1;
      left2->parent = n1;

      //point n1 back to left and right
      n1->left = left1;
      n1->right = left2;
      
      //assign n2 as parent of n's two rightmost children
      right1->parent = n2;
      right2->parent = n2;

      //point n2 back to left and right
      n2->left = right1;
      n2->right = right2;
   }

   string x = midVal;

   //case if adding x to p would make p have 3 items
   if(is3Node(p) && is3Node(n)) {
      if(p->left == n) {
         child1 = n1;
         child2 = n2;
         child3 = p->left;
         child4 = p->right;
      }
      else if (p->right == n) {
         child1 = p->left;
         child2 = p->middle;
         child3 = n1;
         child4 = n2;
      }
      else { //if middle
         child1 = p->left;
         child2 = n1;
         child3 = n2;
         child4 = p->right;
      }
     split(p, x, child1, child2, child3, child4); //now calls split on the children
   }
   
   //case when there are 4 children under a 2 node
   if(is2Node(p)) {
      if(n == root) {
         root = p;
         p->left = n1;
         p->right = n2; 
      }
      else if (p->left == n) {
         p->left = n1;
         p->middle = n2;

         p->large = p->small;
         p->small = x;
      }
      else { //if n is p's right
         p->middle = n1;
         p->right = n2;
         p->large = x;
      }
   }
   return;
}

void Tree::split(Node *n, const string & userWord, Node *l1, Node *l2, Node *r1, Node *r2) {
    string smallVal = smallString(n, userWord);
    string midVal = middleString(n, userWord);
    string largeVal = largeString(n, userWord);
    cout << "small: " << smallVal << endl;
    cout << "middle: " << midVal << endl;
    cout << "large: " << largeVal << endl;

    Node *p = 0;

    if (n == root) {
        p = new Node(midVal);
        root = p;
    }
    else {
        p = n->parent;
    }

    Node *n1 = new Node(smallVal);
    Node *n2 = new Node(largeVal);

    n1->parent = p;
    n2->parent = p;

    if (!isLeafNode(n)) {
        //assign n1 as parent of n's two leftmost children
        l1->parent = n1;
        l2->parent = n1;
        n1->left = l1;
        n1->right = l2;

        //assign n2 as parent of n's two rightmost children
        r1->parent = n2;
        r2->parent = n2;
        n2->left = r1;
        n2->right = r2;
    }

    string x = midVal;

    if (is3Node(p) && is3Node(n)) {
        Node *child1 = 0;
        Node *child2 = 0;
        Node *child3 = 0;
        Node *child4 = 0;

        if (p->left == n) {
            child1 = n1;
            child2 = n2;
            child3 = p->left;
            child4 = p->right;
        }
        else if (p->middle == n) {
            child1 = p->left;
            child2 = n1;
            child3 = n2;
            child4 = p->right;
        }
        else { //if p's right is n
            child1 = p->left;
            child2 = p->middle;
            child3 = n1;
            child4 = n2;
        }
        split(p, x, child1, child2, child3, child4); //recursively call split to insert midVal with new children
    }

    if (is2Node(p)) {
        if (n == root) {
            root = p;
            p->left = n1;
            p->right = n2;
        }
        else if (n == p->left) {
            p->left = n1;
            p->middle = n2;

            p->large = p->small;
            p->small = x;
        }
        else {
            p->middle = n1;
            p->right = n2;
            p->large = x;
        }
    }
}

Node* Tree::ioSuccessor(Node *current, const string & userWord) {
    if (isLeafNode(current)) {
        return current;
    }
    else if (is2Node(current)) {
        if (userWord < current->small) {
            return ioSuccessor(current->left, userWord); //searches left
        }
        else {
            return ioSuccessor(current->right, userWord); //searches right otherwise
        }
    }
    else { //if 3 Node
        if (userWord < current->small) {
            return ioSuccessor(current->left, userWord);
        }
        else if (userWord < current->large) {
            return ioSuccessor(current->middle, userWord);
        }
        else {
            return ioSuccessor(current->right, userWord);
        }
    }
}

void Tree::remove(const string & userWord) {
    Node *current = search(root, userWord);
    Node *leafNode = 0;
    if (current) {
        if (!isLeafNode(current)) {
            Node *nSuccessor = ioSuccessor(current, userWord);
            if (current->small == userWord) {
                swap(current->small, nSuccessor->small);
            }
            else {
                swap(current->large, nSuccessor->large);
            }
            leafNode = nSuccessor;
        }
        else {
            leafNode = current;
        }

        //deletes the item from leafNode
        if (userWord == leafNode->large) {
            leafNode->large = "";
        }
        else {
            leafNode->small = leafNode->large;
            leafNode->large = "";
        }

        //fixes if leafNode contains no items
        if (leafNode->small.empty()) {
            fix(leafNode);
        }
    }
}

Node* Tree::getSibling(Node *current) {
    Node *p = current->parent;
    if (is2Node(p)) {
        if (p->left == current) {
            return p->right;
        }
        else if (p->right == current) {
            return p->left;
        }
    }
    else { //if p is a 3 Node
        if (p->right == current || p->left == current) {
            return p->middle;
        }
        else {
            if (is3Node(p->left) && is3Node(p->right)) {
                return p->right;
            }
            else if (is2Node(p->left) && is2Node(p->right)) {
                return p->left;
            }
            else if (is3Node(p->left)) {
                return p->left;
            }
            else { //if p's right is a 3 Node
                return p->right;
            }
        }
    }
    return 0;
}

void Tree::fix(Node* n) {
    if (n == root) {
        // cout << "n is the root" << endl;
        if (isLeafNode(n)) {
            // cout << "n is a leaf node" << endl;
            delete n;
            root = 0;
            return;
        }
        else {
            // cout << "n is a root with ONE child" << endl;
            // cout << "n's right contains " << "\"" << n->right->small << n->right->large << "\"" << endl;
            // cout << "n's left contains " << "\"" << n->left->small << n->left->large << "\"" << endl;
            if (root->right == 0) {
                root = root->left;
            }
            else {
                root = root->right;
            }
            // cout << "root contains " << root->small << root->large << endl;
        }
        return;
    }
    else {
        Node* p = n->parent;
        Node* s = getSibling(n);
        // cout << "Sibling's small is: " << s->small << endl;
        // cout << "Sibling's large is: " << s->large << endl;

        if (is3Node(s)) {
            //cout << "n's sibling is a 3 Node" << endl;
            if (p->left == n){
                //cout << "n is p's left" << endl;
                if (is2Node(p)){
                    n->small = p->small;
                    p->small = s->small;
                    s->small = s->large;
                    s->large = "";
                }
                else{ //if p is a 3 Node
                    if (is2Node(p->right)) {
                        n->small = p->small;
                        p->small = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                    else { //if p's right is a 3 Node
                        n->small = p->small;
                        p->small = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                }
            }
            else if (p->middle == n) { //p WILL be a 3 Node
                //cout << "n is p's middle" << endl;
                if (p->left == s){
                    n->small = p->small;
                    p->small = s->large;
                    s->large = "";
                }
                else{
                    n->small = p->large;
                    p->large = s->small;
                    s->small = s->large;
                    s->large = "";
                }
            }
            else { //n is p's right
                //cout << "n is p's right" << endl;
                if (is2Node(p)) {
                    n->small = p->small;
                    p->small = s->large;
                    s->large = "";
                }
                else{ //if p is a 3 Node
                    if (is2Node(p->left)) {
                        n->small = p->large;
                        p->large = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                    else{ //if p's left is a 3 Node
                        n->small = p->large;
                        p->large = s->large;
                        s->large = "";
                    }
                }
            }

            //if internal node
            if ((n->left != 0 && n->right == 0) || (n->right != 0 && n->left == 0)) {
                if (p->right == n) {
                    if (n->left == 0){
                        n->left = s->right;
                        s->right = s->middle;
                        s->middle = 0;
                    }
                    else{
                        n->right = n->left;
                        n->left = s->right;
                        s->right = s->middle;
                        s->middle = 0;
                    }
                }
                else {
                    if (n->right == 0) {
                        n->right = s->left;
                        s->left = s->middle;
                        s->middle = 0;
                    }
                    else{
                        n->left = n->right;
                        n->right = s->left;
                        s->left = s->middle;
                        s->middle = 0;
                    }
                }
            }
        }
        else {
            //cout << "n's sibling is a 2 Node" << endl;
            if (is2Node(p)) {
                if (p->left == n) {
                    s->large = s->small;
                    s->small = p->small;
                    p->small = "";
                } 
                else {
                    s->large = p->small;
                    p->small = "";
                }
            }
            else {
                if (p->left == n) {
                    //cout << "n is p's left" << endl;
                    if (is2Node(p->right)) {
                        s->large = s->small;
                        s->small = p->small;
                        p->small = p->large;
                        p->large = "";
                        p->left = s;
                        p->middle = 0;
                    }
                    else {
                        n->small = p->small;
                        p->small = s->small;
                        s->small = p->large;
                        p->large = p->right->small;
                        p->right->small = p->right->large;
                        p->right->large = "";
                    }
                }
                else if (p->middle == n) {
                    //cout << "n is p's middle" << endl;
                    s->large = p->small;
                    p->small = p->large;
                    p->large = "";
                    p->middle = 0;
                }
                else { //n is p's right
                    //cout << "n is p's right" << endl;
                    if (is2Node(p->left)) {
                        s->large = p->large;
                        p->large = "";
                        p->right = s;
                        p->middle = 0;
                    }
                    else {
                        n->small = p->large;
                        p->large = s->small;
                        s->small = p->small;
                        p->small = p->left->large;
                        p->left->large = "";
                    }
                }
            }

            //if n is internal (n is empty, but has a child)
            if ((n->left != 0 && n->right == 0) || (n->right !=0 && n->left == 0)) {
                if (p->right == n) {
                    s->middle = s->right;
                    if (n->left == 0) {
                        s->right = n->right;
                    }
                    else {
                        s->right = n->left;
                    }
                }
                else {
                    s->middle = s->left;
                    if (n->right == 0) {
                        s->left = n->left;
                    }
                    else {
                        s->left = n->right;
                    }
                }
            }

            delete n;
            n = 0;

            //call fix if p is empty
            if (p->small.empty() && p->large.empty()){
                fix(p);
            }
        }
    }
}

void Tree::deleteNodes(Node *current) {
    //starts deleting from the leaves and goes up
    if (isLeafNode(current)) {
        delete current;
        current = 0;
    }
    else if (is2Node(current)) {
        deleteNodes(current->left);
        deleteNodes(current->right);
    }
    else { //if current is a 3 Node
        deleteNodes(current->left);
        deleteNodes(current->middle);
        deleteNodes(current->right);
    }
}
#include "BSTree.h"
#include <iostream>

using namespace std;

void BSTree::insert(const string & newWord) {
    Node* treeNode = new Node(newWord, 1);
    if (root == 0) { // constructs a new node if empty
        root = treeNode; // assign treeNode to root
        return;
    }
    Node* current = root;
    Node* temp = 0;
    //finds the parent node of where to insert
    while (current != 0) { // until LEAF node is reached
         temp = current;
         if (newWord == current->word) {
             current->counter++;
             return;
         }
         else if (newWord < current->word) {
             current = current->left;
         }
         else {
             current = current->right;
         }
     }

     //chooses where to insert node (left or right)
     if (newWord < temp->word) { // inserts node to left or right
         temp->left = treeNode;
         treeNode->parent = temp;
     }
    else {
        temp->right = treeNode;
        treeNode->parent = temp;
    }
}

void BSTree::inOrder(Node *current) const {
    if (current == 0) {
        return;
    }
    inOrder(current->left); // recursively calls on left subtree
    cout << current->word << "(" << current->counter << "), ";
    inOrder(current->right); // recursively calls on right subtree
}

void BSTree::inOrder() const {
    inOrder(root);
}

void BSTree::postOrder(Node *current) const {
    if (current == 0) {
        return;
    }
    postOrder(current->left); // recursively calls on left subtree
    postOrder(current->right); // recursively calls on right subtree
    cout << current->word << "(" << current->counter << "), ";
}

void BSTree::postOrder() const {
    postOrder(root);
}

void BSTree::preOrder(Node *current) const {
    if (current == 0) {
        return;
    }
    cout << current->word << "(" << current->counter << "), ";
    preOrder(current->left); // recursively calls on left subtree
    preOrder(current->right); // recursively calls on right subtree
}

void BSTree::preOrder() const {
    preOrder(root);
}

string BSTree::largest() const {
    if (root == 0) {
        return "";
    }
    Node *current = root; // start at the root
    string large = current->word;
    while (current->right != 0) { // keeps going down the right
        current = current->right;
        large = current->word;
    }
    return large;
}

string BSTree::smallest() const {
    if (root == 0) {
        return "";
    }
    Node *current = root; // start at the root
    string small = current->word;
    while (current->left != 0) { // keeps going down the left
        current = current->left;
        small = current->word;
    }
    return small;
}

bool BSTree::search(const string & userWord) const {
    return search(root, userWord);
}

Node* BSTree::search(Node* current, const string & userWord) const {
    if (current == 0) {
        return 0;
    }
    else if (current->word == userWord) {
        return current;
    }
    else if (current->word > userWord) { // checks left and returns pointer to node
        return search(current->left, userWord);
    }
    else {
        return search(current->right, userWord); // checks right and returns pointer to node
    }
}

int BSTree::height(const string & userWord) const {
    Node *isFound = search(root, userWord); // checks if word exists and locates it
    if (isFound == 0) {
        return -1;
    }
    if (isFound->left == 0 && isFound->right == 0) {
        return 0;
    }
    return height(isFound);
}

int BSTree::height(Node *current) const {
    if (current == 0) { // base case
        return -1;
    }
    else if (current->left == 0 && current->right == 0) {
        return 0;
    }

    int leftSide = height(current->left); // recursively assigns and finds height of left side
    int rightSide = height(current->right);// recursively assigns and finds height of right side
    if (rightSide >= leftSide) {
        return 1 + rightSide;
    }
    else {
        return 1 + leftSide;
    }
    return 0;
}

Node* BSTree::leftMax(Node* current) {
    Node* max = current->left;
    while (max->right != 0) { // keeps going to right of left tree until it finds biggest value
        max = max->right;
    }
    return max;
}

Node* BSTree::rightMin(Node* current) {
    Node *min = current->right;
    while (min->left != 0) { // keeps going to left of right tree until it finds smallest value
        min = min->left;
    }
    return min;
}

void BSTree::remove(Node* current, const string & userWord) {
    Node* tempParent = current->parent;
    
    if (!search(userWord) || root == 0) { // if word not found
        return;
    }
    else if (current->counter > 1) {
        current->counter--;
        return;
    }
    else if (current->left == 0 && current->right == 0) { // if other leaf node
        if (tempParent == 0) { // if only ONE node in tree
            root = 0;
        }
        else if (tempParent->left == current) {
            tempParent->left = 0;
        }
        else {
            tempParent->right = 0;
        }
        delete current;
        current = 0;
        return;
    }
    else if (current->left == 0) { // if ONLY left child exists
        Node *tempMin = rightMin(current);

        //sets all of tempMax's word to current's word
        current->word = tempMin->word;
        current->counter = tempMin->counter;
        if (tempMin->counter > 1) {
            tempMin->counter--;
        }
        remove(tempMin, tempMin->word);
    }
    else { // if right child or both exist
        Node *tempMax = leftMax(current);

        //sets all of tempMin's word to current's word
        current->word = tempMax->word;
        current->counter = tempMax->counter;
        if (tempMax->counter > 1) {
            tempMax->counter--;
        }
        remove(tempMax, tempMax->word);
    }
    return;
}

void BSTree::remove(const string & userWord) {
    Node *current = search(root, userWord);
    if (root == 0 || !search(userWord)) { // empty tree
        return;
    }
    remove(current, userWord);
}
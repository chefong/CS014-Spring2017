#include "AVLTree.h"
#include <iostream>
#include <fstream>

using namespace std;

void AVLTree::insert(const string & userWord){
    //creates a new Node to insert
    Node* treeNode = new Node(userWord);
    Node* n = 0;
    Node* nPar = 0;
    n = root;

    if (root == 0) {
        root = treeNode;
        root->balanceNum = -1;
        return;
    }
    
    if (search(userWord)) { //return if word exists
        return;
    }

    while (n) { //locates where to insert
        nPar = n;
        if (treeNode->data < nPar->data) {
            n = nPar->left;
        }
        if (treeNode->data >= nPar->data) {
            n = nPar->right;
        }
    }
    if (treeNode->data < nPar->data) { //inserts the node
        nPar->left = treeNode;
    }
    else if (treeNode->data > nPar->data) {
        nPar->right = treeNode;
    }
    treeNode->parent = nPar;

    rebalance(root);

    while (findUnbalancedNode(treeNode) != 0) {
        rotate(findUnbalancedNode(treeNode));
        rebalance(root);
    }
}

int AVLTree::balanceFactor(Node* current){
    int right = 0;
    int left = 0;

    if (current == 0){
        return -1;
    }

    if (current->left == 0){ //gets left's height
        left = -1;
    }
    else {
        left = height(current->left); //gets the height of the left subtree
    }

    if (current->right == 0){ //gets right's height
        right = -1;
    }
    else {
        right = height(current->right); //gets the height of the right subtree
    }

    return left - right;
}

void AVLTree::printBalanceFactors(){
    rebalance(root);
    printBalanceFactors(root);
    cout << endl;
}

int AVLTree::height(Node* current){
    int leftH = 0;
    int rightH = 0;

    if (current == 0) {
        return 0;
    }

    if (current->left != 0) { //gets height of left
        leftH = height(current->left);
    }
    if (current->right != 0) { //gets height of right
        rightH = height(current->right); 
    }
    
    if (leftH > rightH) {
        return 1 + leftH;
    }
    if (current->left == 0 && current->right == 0){
        return 0;
    }
    return 1 + rightH;
}

Node* AVLTree::findUnbalancedNode(Node* current) {
    Node *n = current;

    while (n != 0){
        if (balanceFactor(n) >= 2 || balanceFactor(n) <= -2){
            return n;
        }
        n = n->parent;
    }
    return 0;
}

void AVLTree::rotate(Node* A){
    if (balanceFactor(A) == 2 && balanceFactor(A->left) == 1) { //case of L L
        rotateRight(A);
    }
    else if (balanceFactor(A) == -2 && balanceFactor(A->right) == -1){ //case of R R
        rotateLeft(A);
    }
    else if (balanceFactor(A) == 2 && balanceFactor(A->left) == -1){ //case of L R
        rotateLeft(A->left);
        rotateRight(A);
    }
    else { //case R L
        rotateRight(A->right);
        rotateLeft(A);
    }

    rebalance(root);
}

Node* AVLTree::rotateLeft(Node* A){
    Node* P = A->parent;
    Node* B = A->right;
    Node* n = B->left;

    B->left = A;
    A->right = n;
    B->parent = A->parent;
    A->parent = B;

    if (P == 0){
        root = B;
    }
    else if (P != 0 && P->data > A->data){
        P->left = B;
    }
    else if (P != 0 && P->data < A->data){
        P->right = B;
    }

    return B;
}

Node* AVLTree::rotateRight(Node* A){
    Node* P = A->parent;
    Node* B = A->left;
    Node* n = B->right;

    B->right = A;
    A->left = n;
    B->parent = A->parent;
    A->parent = B;

    if (P == 0) {
        root = B;
    }
    else if (P->data > A->data){
        P->left = B;
    }
    else if (P->data < A->data){
        P->right = B;
    }

    return B;
}

void AVLTree::printBalanceFactors(Node* n){
    if (n) {
        printBalanceFactors(n->left);
        cout << n->data << "(" << n->balanceNum << "), ";
        printBalanceFactors(n->right);
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

void AVLTree::rebalance(Node* n) {
    if (n) {
        n->balanceNum = balanceFactor(n);
        rebalance(n->left);
        rebalance(n->right);
    }
}

bool AVLTree::search(const string & userWord) const {
    Node* current = root;

    while (current) {
        if (current->data > userWord){
            current = current->left;
        }
        else if (current->data < userWord){
            current = current->right;
        }
        else if (current->data == userWord){
            return true;
        }
    }

    return false;
}
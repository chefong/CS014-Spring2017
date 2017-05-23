#include "arithmeticExpression.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

arithmeticExpression::arithmeticExpression(const string & val) {
    infixExpression = val;
    root = 0;
}

void arithmeticExpression::infix() {
    infix(root);
}

void arithmeticExpression::infix(TreeNode *current) {
    if (current->left != 0 && current->right !=0) {
        cout << "(";
        infix(current->left); // recursively calls on the left tree branch
        cout << current->data;
        infix(current->right); // recursively calls on the right tree branch
        cout << ")";
    }
    else {
        cout << current->data;
    }
}

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode *current) {
    if (current->left != 0 && current->right != 0) {
        cout << current->data;
        prefix(current->left); // recursively calls on the left tree branch
        prefix(current->right); // recursively calls on the right tree branch
    }
    else {
        cout << current->data;
    }
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode *current) {
    if (current->left != 0 && current->right != 0) {
        postfix(current->left);
        postfix(current->right);
        cout << current->data;
    }
    else {
        cout << current->data;
    }
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

void arithmeticExpression::visualizeTree(ofstream & out, TreeNode * current) {
    if (current) {
        out << current->key << " [ label="" << current->data << ""];" << endl;
        visualizeTree(out, current->left);
        visualizeTree(out, current->right);
        if(current->right) {
            out << current->key << " -> " << current->right->key << ";" << endl;
        }
        if(current->left) {
            out << current->key << " -> " << current->left->key << ";" << endl;
        }
    }
}

void arithmeticExpression::buildTree() {
    string postfixExpression = infix_to_postfix(); // converts infix to postfix
    TreeNode *child1 = 0;
    TreeNode *child2 = 0;
    stack<TreeNode*> expressionTree;
    char key = 'a';

    for (unsigned i = 0; i < postfixExpression.size(); ++i) {
        if (postfixExpression.at(i) == '+' || postfixExpression.at(i) == '-' ||
        postfixExpression.at(i) == '*' || postfixExpression.at(i) == '/') {
            child1 = expressionTree.top(); // gets the right
            expressionTree.pop();
            child2 = expressionTree.top(); // gets the left
            expressionTree.pop();
            TreeNode *op = new TreeNode(postfixExpression.at(i), key + i); // creates new root of a tree
            op->left = child2; // assigns the left of new root
            op->right = child1; // assigns the right of new root
            expressionTree.push(op); // pushes the new root to stack
        }
        else {
            TreeNode *operand = new TreeNode(postfixExpression.at(i), key + i);
            expressionTree.push(operand); // pushes new tree of operand to stack
        }
    }

    root = expressionTree.top(); // assigns the ultimate root
}
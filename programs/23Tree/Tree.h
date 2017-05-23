#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>

class Tree {
    public:
        
        Tree() : root(0) {}
        ~Tree();
        
        //Traverse and print the tree in preorder notation.
        void preOrder() const;

        //Traverse and print the tree in inorder notation.
        void inOrder() const;

        //Traverse and print the tree in postorder notation.
        void postOrder() const;
        
        //Insert an item into the 2-3 tree. Be sure to maintain the 2-3 tree properties.
        void insert(const string &);

        //Remove a specified item from the tree. Be sure to maintain the 2-3 tree properties. 
        //Some removes can be resolved in multiple ways. To make sure that your output matches 
        //mine exactly, follow the examples listed in the notes below. If an ambiguous case 
        //arises that I have not specified, ask me and I will make the specification.
        void remove(const string &);

        //Search for a specified item in the tree. Return true if the item exists in the tree. 
        //Return false if the item does not exist.
        bool search(const string &) const;

    private:

        //Node pointer for the root of the tree.
        Node *root;

        //Recursively searches for the string passed in and returns a Node pointer to the string.
        Node* search(Node *, const string &) const;

        //Searches for the inorder successor of the passed in node
        Node* ioSuccessor(Node *, const string &);

        //Returns the sibling of the passed in node
        Node* getSibling(Node *);

        //Splits a node as a result of having 3 items after inserting.
        void split(Node *, const string &, Node *, Node *, Node *, Node *);

        //Recursive function for preOrder.
        void preOrder(Node *) const;

        //Recursive function for inOrder.
        void inOrder(Node *) const;

        //Recursive function for postOrder.
        void postOrder(Node *) const;

        //completes the deletion when node n is empty by either removing the root, 
        //redistributing values, or merging nodes.
        //Note: if n is internal, it has only one child
        void fix(Node *);

        //Used in the destructor to recursively dellocate memory for each node
        void deleteNodes(Node *);

        //Checks if node is a LEAF node.
        bool isLeafNode(Node *) const;

        //Checks if node is a 2 node.
        bool is2Node(Node *) const;

        //Checks if node is a 3 node.
        bool is3Node(Node *) const;

        //Locates and returns the small data of the Node and string passed in.
        string smallString(Node *, const string &);

        //Locates and returns the middle data of the Node and string passed in.
        string middleString(Node *, const string &);

        //Locates and returns the large data of the Node and string passed in.
        string largeString(Node *, const string &);
};

#endif
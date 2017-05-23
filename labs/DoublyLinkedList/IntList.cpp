#include <iostream>

using namespace std;

#include "IntList.h"

IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList() {
    if (!empty()) {
        pop_front();
    }
    delete dummyHead;
    delete dummyTail;
    dummyHead = 0;
    dummyTail = 0;
}

void IntList::push_front(int value) {
    IntNode *temp = new IntNode(value);
    temp->next = dummyHead->next;
    temp->next->prev = temp;
    temp->prev = dummyHead;
    dummyHead->next = temp;
}

void IntList::pop_front() {
    if (!empty()) {
        IntNode *temp = dummyHead->next;
        dummyHead->next = temp->next;
        temp->next->prev = dummyHead;
        delete temp;
        temp = 0;
    }
}

void IntList::push_back(int value) {
    IntNode *prevNode = dummyTail->prev;
    IntNode *temp = new IntNode(value);
    temp->next = dummyTail;
    prevNode->next = temp;
    dummyTail->prev = temp;
    temp->prev = prevNode;
}

void IntList::pop_back() {
    if (!empty()) {
        IntNode *temp = dummyTail->prev;
        dummyTail->prev = temp->prev;
        temp->prev->next = dummyTail;
        delete temp;
        temp = 0;
    }
}

bool IntList::empty() const {
    if (dummyHead->next == dummyTail && dummyTail->prev == dummyHead) {
        return true;
    }
    else {
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    for (IntNode *current = rhs.dummyHead->next; current != rhs.dummyTail; current = current->next) {
        out << current->data;
        if (current->next != rhs.dummyTail) {
            out << " ";
        }
    }
    return out;
}

void IntList::printReverse() const {
    for (IntNode *current = dummyTail->prev; current != dummyHead; current = current->prev) {
        cout << current->data;
        if (current->prev != dummyHead) {
            cout << " ";
        }
    }
}
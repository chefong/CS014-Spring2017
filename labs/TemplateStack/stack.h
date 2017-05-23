#include <iostream>
#include <stdexcept>
#define MAX_SIZE 20
#ifndef STACK_H
#define STACK_H

using namespace std;

template <typename T>
class stack{
    public:
        stack();
        void push(T val);
        void pop();
        T top();
        bool empty();
    private:
        T data[MAX_SIZE];
        int size;
};

//constructs an empty stack.
template <typename T>
stack<T>::stack() {
    size = 0;
}
    
//inserts a new element (val) of type T (T could be integer or string) 
//into the data. If the data array is full, this function should throw 
//an overflow_error exception with error message "Called push on full stack.".
template <typename T>
void stack<T>::push(T val) {
    if (size == 20){
        throw overflow_error("Called push on full stack.");
    }
    else {
        data[size] = val;
        size++;
    }   
}

//removes the last element from data. If the data array is empty, this 
//function should throw an outofrange exception with error message "Called 
//pop on empty stack.".
template <typename T>
void stack<T>::pop() {
    if (size == 0){
        throw out_of_range("Called pop on empty stack.");
    }
    else { 
        size--;
    }
} 

//returns the top element of stack (last inserted element). If stack is empty,
//this function should throw an underflow_error exception with error message 
//"Called top on empty stack.".
template <typename T>
T stack<T>::top() {
    if (size == 0) {
        throw underflow_error("Called top on empty stack.");
    }
    return data[size -1];
}
    
    
//returns true if the stack is empty otherwise it returns false.
template <typename T>
bool stack<T>::empty() {
    if (size == 0){
        return true;
    }
    else return false;
    }

#endif
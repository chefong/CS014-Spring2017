#include <iostream>

using namespace std;

#include "IntList.h"

int main() {
    IntList l1;

    cout << "Test print empty" << endl;
    cout << l1 << endl;

    cout << "Test push front" << endl;
    l1.push_front(1);
    cout << l1 << endl;

    cout << "Test push back" << endl;
    l1.push_back(2);
    cout << l1 << endl;

    cout << "Test pop front" << endl;
    l1.pop_front();
    cout << l1 << endl;

    cout << "Test pop back" << endl;
    l1.pop_back();
    cout << l1 << endl;

    cout << "Pushing front 2" << endl;
    l1.push_front(2);
    cout << "Pushing back 3" << endl;
    l1.push_back(3);
    cout << "Pushing front 1" << endl;
    l1.push_front(1);
    cout << "Pushing back 4" << endl;
    l1.push_back(4);
    cout << l1 << endl;

    cout << "Testing print reverse" << endl;
    l1.printReverse();
    cout << endl;

    cout << "Print empty (1 for true, 0 for false)" << endl;
    if (l1.empty()) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
}
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned min = index;
    for (unsigned i = index + 1; i < vals.size(); ++i) {
        if (vals.at(i) < vals.at(min)) {
            min = i;
        }
    }
    return min;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    for (unsigned start = 0; start < vals.size(); ++start) {
        unsigned minLoc = min_index(vals, start);
        swap(vals.at(start), vals.at(minLoc));
    }
}

template<typename T>
void print(vector<T> &vals) {
    for (unsigned i = 0; i < vals.size(); ++i) {
        cout << vals.at(i) << " ";
    }
}

template<typename T>
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main() {
    vector<int> v;
    vector<string> s;
    vector<double> d;

    int userIn;
    int num = 0;
    string userStr;
    double userDoub;

    cout << "input 5 integer values for vector v: " << endl;
    while (num < 5) {
        cin >> userIn;
        v.push_back(userIn);
        num++;
    }
    num = 0; // resets counter

    cout << "input 5 string values for vector s: " << endl;
    while (num < 5) {
        cin >> userStr;
        s.push_back(userStr);
        num++;
    }
    num = 0; // resets counter

    cout << "input 5 double values for vector d: " << endl;
    while (num < 5) {
        cin >> userDoub;
        d.push_back(userDoub);
        num++;
    }
    num = 0; // resets counter
    cout << endl;

    print(v);
    cout << endl;
    selection_sort(v);
    print(v);
    cout << endl;
    cout << endl;

    print(s);
    cout << endl;
    selection_sort(s);
    print(s);
    cout << endl;
    cout << endl;

    print(d);
    cout << endl;
    selection_sort(d);
    print(d);
    cout << endl;
    cout << endl;

    /////////////////////////////////////////////////////////////////////////

    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    
    cout << "Size of vector vals: " << vals.size() << endl;
    while(--numOfRuns >= 0){
        try {
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch (const std::out_of_range& excpt) {
            cout << "out of range exception occured" << endl;
        }
    }

    return 0;
}
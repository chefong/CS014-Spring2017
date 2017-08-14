#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Warning this type of initialization requires a C++11 Compiler
    vector<int> intVec;
    intVec.push_back(5);
    intVec.push_back(9);
    intVec.push_back(11);
    intVec.push_back(2);

    sort(intVec.begin(), intVec.end());

    for (int i = 0; i < intVec.size(); ++i) {
      cout << intVec.at(i) << endl;
    }
}

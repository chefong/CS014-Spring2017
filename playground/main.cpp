#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class User {
    public:
        User();
        string GetUsername() const;
        string GetPassword() const;
        void SetUsername(const string & username);
        void SetPassword(const string & password);
        void print() const;
    private:
        vector<T> v;
};

int main() {
    Person A;
}
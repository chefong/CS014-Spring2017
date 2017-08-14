#ifndef JUG_H
#define JUG_H

#include <vector>
#include <string>
#include <list>
#include <climits>

using namespace std;

//using Vertex from Lab 9
struct Vertex {
  public:
    pair<int, int> neighbors [6];
    pair<int, int> state;
    string label;
    int distance;
    string color;
    Vertex* prev;

    Vertex():state(0,0),label(""),distance(INT_MAX),color("WHITE"),prev(0){}
    ~Vertex(){}
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int capA;
        int capB;
        int goal;
        int costFillA;
        int costFillB;
        int costEmptyA;
        int costEmptyB;
        int costPourAB;
        int costPourBA;
        vector<Vertex> adjacencyList;

        int find(Vertex &);
        void fillA(Vertex &);
        void fillB(Vertex &);
        void emptyA(Vertex &);
        void emptyB(Vertex &);
        void pourAtoB(Vertex &);
        void pourBtoA(Vertex &);
        void makeGraph(vector<Vertex> &);
        bool exists(Vertex &);
        void dijkstra();
};

#endif

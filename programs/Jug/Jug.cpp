#include "Jug.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <climits>

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
     capA(Ca), capB(Cb), goal(N), costFillA(cfA), costFillB(cfB), costEmptyA(ceA), costEmptyB(ceB),
     costPourAB(cpAB), costPourBA(cpBA) {

       if(!(Ca > 0 && Ca <= Cb) || !(Cb > goal && Cb <= 1000) ){
           return;
       }
       if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0){
           return;
       }

       makeGraph(adjacencyList);
     }

Jug::~Jug() {
  //not needed
}

void Jug::fillA(Vertex & v) { //fill first jug with A's capacity
  v.state.first = capA;
}

void Jug::fillB(Vertex & v) { //fill second jug with B's capacity
  v.state.second = capB;
}

void Jug::emptyA(Vertex & v) { //make first jug empty
  v.state.first = 0;
}

void Jug::emptyB(Vertex & v) { //make second jug empty
  v.state.second = 0;
}

void Jug::pourAtoB(Vertex & v) { //pours from A to B until B is full or A is empty
  while (v.state.first != 0 && v.state.second != capB) {
    v.state.first--;
    v.state.second++;
  }
}

void Jug::pourBtoA(Vertex & v) { //pours from B to A until A is full or B is empty
  while (v.state.second != 0 && v.state.first != capA) {
    v.state.first++;
    v.state.second--;
  }
}

void Jug::makeGraph(vector<Vertex> & v) {
  Vertex a;
  Vertex initial;
  v.push_back(a); //start graph at (0,0)

  for (unsigned int j = 0; j < v.size(); j++) {
    initial = v.at(j);
    Vertex v1 = initial;
    Vertex v2 = initial;
    Vertex v3 = initial;
    Vertex v4 = initial;
    Vertex v5 = initial;
    Vertex v6 = initial;

    fillA(v1);
    fillB(v2);
    emptyA(v3);
    emptyB(v4);
    pourAtoB(v5);
    pourBtoA(v6);

    //checks if state is in adjacency list; if not, add state
    if (!exists(v1)) {
       adjacencyList.push_back(v1);
    }
    if (!exists(v2)) {
       adjacencyList.push_back(v2);
    }
    if (!exists(v3)) {
       adjacencyList.push_back(v3);
    }
    if (!exists(v4)) {
       adjacencyList.push_back(v4);
    }
    if (!exists(v5)) {
       adjacencyList.push_back(v5);
    }
    if (!exists(v6)) {
       adjacencyList.push_back(v6);
    }

    initial.neighbors[0] = pair<int,int>(find(v1),costFillA);
    initial.neighbors[1] = pair<int,int>(find(v2),costFillB);
    initial.neighbors[2] = pair<int,int>(find(v3),costEmptyA);
    initial.neighbors[3] = pair<int,int>(find(v4),costEmptyB);
    initial.neighbors[4] = pair<int,int>(find(v5),costPourAB);
    initial.neighbors[5] = pair<int,int>(find(v6),costPourBA);

    v.at(j) = initial;
  }

  //  for (unsigned i = 0; i < adjacencyList.size(); i++) {
  //     cout << adjacencyList.at(i).state.first << ',' <<  adjacencyList.at(i).state.second << endl;
  //     for (list<pair<int,int> >::iterator it = adjacencyList.at(i).neighbors.begin(); it != adjacencyList.at(i).neighbors.end(); ++it) {
  //       cout << it->first << ", " << it->second << endl;
  //     }
  //  }

}

bool Jug::exists(Vertex & v) {
  for (unsigned i = 0; i < adjacencyList.size(); ++i) {
    if (adjacencyList.at(i).state.first == v.state.first && adjacencyList.at(i).state.second == v.state.second) {
      return true;
    }
  }
  return false;
}

int Jug::find(Vertex & v) {
  for (unsigned i = 0; i < adjacencyList.size(); ++i) {
    if (adjacencyList.at(i).state.first == v.state.first && adjacencyList.at(i).state.second == v.state.second) {
      return i;
    }
  }
  return -1;
}

int Jug::solve(string & solution) {
  stringstream ss;

  //verify costs are positive
  if (costFillA < 0 || costFillB < 0 || costEmptyA < 0 || costEmptyB < 0 || costPourAB < 0 || costPourBA < 0) {
    solution = "";
    return -1;
  }
  //verify 0 < Ca <= Cb
  if (capA <= 0 || capA > capB || capB <= 0) {
    solution = "";
    return -1;
  }
  //verify N <= Cb <= 1000
  if (capB < goal || capB > 1000 || goal > 1000) {
    solution = "";
    return -1;
  }

  int index = -1; //if index changes, then no solution exists
  for(unsigned i = 0; i < adjacencyList.size(); ++i){
      if(adjacencyList.at(i).state.first == 0 && adjacencyList.at(i).state.second == goal){
          index = i;
      }
  }

  //error if index wasn't assigned
  if(index == -1){
      solution = "";
      return 0;
  }

  dijkstra(); //performs dijkstra's by visiting and assigning minimum distances when optimal

  stack<Vertex*> vStack;
  Vertex *current = &adjacencyList.at(index);

  //pushes the GOAL vertex and pushes its previous vertices after
  while(current != 0){
      vStack.push(current);
      current = current->prev;
  }

  //if current and before vertex indices match, print out the proper action
  while(vStack.size() - 1 != 0){
      current = vStack.top();
      vStack.pop();
      Vertex *before = vStack.top();

      if (&adjacencyList.at(current->neighbors[0].first) == before) {
        ss << "fill A" << endl;
      }
      if (&adjacencyList.at(current->neighbors[1].first) == before) {
        ss << "fill B" << endl;
      }
      if (&adjacencyList.at(current->neighbors[2].first) == before) {
        ss << "empty A" << endl;
      }
      if (&adjacencyList.at(current->neighbors[3].first) == before) {
        ss << "empty B" << endl;
      }
      if (&adjacencyList.at(current->neighbors[4].first) == before) {
        ss << "pour A B" << endl;
      }
      if (&adjacencyList.at(current->neighbors[5].first) == before) {
        ss << "pour B A" << endl;
      }
  }

  ss << "success " << adjacencyList.at(index).distance;
  solution = ss.str();

  return 1;
}

void Jug::dijkstra() { //used dijkstra's algorithm from ZyBooks
  queue<Vertex*> q; //unvisited queue of vertices

  //initialize single source
  for (unsigned i = 0; i < adjacencyList.size(); ++i) {
    adjacencyList.at(i).distance = INT_MAX;
    adjacencyList.at(i).prev = 0;
    q.push(&adjacencyList.at(i));
  }

  adjacencyList.at(0).distance = 0;

  while (!q.empty()) {

    Vertex *currentV = q.front(); //visits vertex and assigns to currentV
    q.pop(); //removes the top of the queue now that it's assigned to currentV

    for (unsigned i = 0; i < 6; ++i) {
      int edgeWeight = currentV->neighbors[i].second;
      int alternativePathDistance = currentV->distance + edgeWeight;

      //relaxation
      if (alternativePathDistance < adjacencyList.at(currentV->neighbors[i].first).distance) {
        adjacencyList.at(currentV->neighbors[i].first).distance = alternativePathDistance;
        adjacencyList.at(currentV->neighbors[i].first).prev = currentV;
      }
    }

    // cout << currentV->distance << endl;
  }
}

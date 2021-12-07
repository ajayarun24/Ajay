#pragma once

#include "parsing.h"
#include <vector>
#include <utility>

using std::vector;
using std::pair;


class RoadTripGraph {
    public:
    RoadTripGraph(string placesFileName, string stateFileName);

    void createGraph();

    bool checkNeighbor(string name, vector<string> neighbors) ;

    vector<Parsing::Location> KruskalsMST();

    vector<Parsing::Location> BFS(int start, int end);

    void printBFS(int start, int end);

    void union1 (int i, int j);

    int find(int i);

    vector<vector<double> > adjacencyMatrix;

    vector<vector<Parsing::Location*> > adjacencyList;

    vector<Parsing::Location> locations;

    vector<int> parent;

    
};
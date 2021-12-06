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

    static bool isValidEdge(int u, int v, vector<bool> inMST);

    vector<Parsing::Location> primMST(vector<vector<double> > weights);

    vector<vector<double> > adjacencyMatrix;

    vector<vector<Parsing::Location*> > adjacencyList;

    vector<Parsing::Location> locations;


};
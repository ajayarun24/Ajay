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

    
    vector<vector<double>> adjacencyMatrix;

    vector<vector<Parsing::Location*>> adjacencyList;

    vector<Parsing::Location> locations;
};
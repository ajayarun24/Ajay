#pragma once

#include "parsing.h"
#include <vector>

using std::vector;

class BreadthFirstSearch {
    BreadthFirstSearch(vector<vector<double>> aM,vector<vector<Parsing::Location*>> aL,
    vector<Parsing::Location> l);

    vector<Parsing::Location> doBFS(int start);

    vector<vector<double>> adjacencyMatrix;

    vector<vector<Parsing::Location*>> adjacencyList;

    vector<Parsing::Location> locations;

};
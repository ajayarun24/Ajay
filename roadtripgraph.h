#pragma once


#include <vector>
#include <utility>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "roadtripgraph.h"
#include "calculator.h"
#include <math.h>
#include <iostream>
#include "parsing.h"

using std::vector;
using std::pair;
using cs225::PNG;
using cs225::HSLAPixel;

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
    
    std::pair<vector<Parsing::Location>, double> Dijkstra(int start, int end);

    void printDijkstra(int start, int end);

    static PNG addPoints(PNG image, std::vector<Parsing::Location> attractions);

    static void addLines(PNG image, std::vector<Parsing::Location> attractions);

    static void drawImage(std::vector<Parsing::Location> attractions);
};
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
    // Constructor
    RoadTripGraph(string placesFileName, string stateFileName);

    // Creates adjacency matrix and adjacency list
    void createGraph();

    // Checks if attraction is in the neigboring state
    bool checkNeighbor(string name, vector<string> neighbors) ;

    vector<Parsing::Location> KruskalsMST(bool shouldPrint);

    // BFS from start to end point
    std::pair<vector<Parsing::Location>, double> BFS(int start, int end);

    // Prints BFS
    void printBFS(int start, int end);

    void union1 (int i, int j);

    int find(int i);

    vector<vector<double> > adjacencyMatrix;

    vector<vector<Parsing::Location*> > adjacencyList;

    vector<Parsing::Location> locations;

    //Disjoint set
    vector<int> parent;

    // Dijktra's from start to end point
    std::pair<vector<Parsing::Location>, double> Dijkstra(int start, int end);

    // Prints Dijkstra's
    void printDijkstra(int start, int end);

    static PNG addPoints(PNG image, std::vector<Parsing::Location> attractions);

    static void addLines(PNG image, std::vector<Parsing::Location> attractions);

    static void drawImage(std::vector<Parsing::Location> attractions);

    static void runProgram();
};
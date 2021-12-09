
#include <iostream>
#include <string>
#include "parsing.h"
#include <stdlib.h>
#include "calculator.h"
#include "roadtripgraph.h"
using std::vector;
using ::Parsing;
using std::cout;
using std::endl;
using ::RoadTripGraph;




int main() {
    //Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

   // vector<Parsing::Location> i = graph.KruskalsMST();
    vector<Parsing::Location> bfs = graph.BFS(0, 12);
   // graph.printBFS(0, 4);
   // graph.printDijkstra(1, 14);
    RoadTripGraph::drawImage(bfs);


    return 0;
}



#include <iostream>
#include <string>
#include "parsing.h"
#include <stdlib.h>
#include "calculator.h"
#include "roadtripgraph.h"

using ::Parsing;

int main() {
    //Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    return 0;
}


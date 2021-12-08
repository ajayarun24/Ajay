
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

static void printAdjMatrix(RoadTripGraph graph)
{
    vector<vector<double> > temp_matrix = graph.adjacencyMatrix;

    for (int i = 0; i < (int)graph.adjacencyList.size(); i++)
    {
        cout << i;
        for (int j = 0; j < (int)graph.adjacencyList[i].size(); j++)
        {
            if (!(graph.adjacencyList[i][j] == NULL))
            {
                if (j == (int)graph.adjacencyList[i].size() - 1)
                {
                    cout << " -> " << graph.adjacencyList[i][j]->priority << endl;
                    break;
                }
                else
                    cout << " -> " << graph.adjacencyList[i][j]->priority;
            }
        }
        cout << "\n================================================================================== \n " << endl;
    }
}



int main() {
    //Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    vector<Parsing::Location> i = graph.KruskalsMST();
    graph.printBFS(95, 96);
    graph.printDijkstra(1, 14);

    cout << "\n================================================================================== \n " << endl;

    return 0;
}


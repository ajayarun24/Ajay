
#include <iostream>
#include <string>
#include "parsing.h"
#include <stdlib.h>
#include "calculator.h"
#include "roadtripgraph.h"
#include "testing.h"
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

static vector<vector<double> > testPrims(){
    vector<vector<double> > tester;
    vector<double> one, two, three, four, five;
    one.insert(one.end(), {-1, 2, -1, 6, -1});
    two.insert(two.end(), {2, -1, 3, 8, 5});
    three.insert(three.end(), {-1, 3, -1, -1, 7});
    four.insert(four.end(), {6, 8, -1, -1, 9});
    five.insert(five.end(), {-1, 5, 7, 9, -1});

    tester.insert(tester.end(), {one, two, three, four, five});
    
    return tester;
}



int main() {
    //Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    //graph.KruskalsMST();

    graph.printBFS(6, 7);



    
    return 0;
}



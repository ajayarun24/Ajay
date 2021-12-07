#include "roadtripgraph.h"
#include "parsing.h"
#include "calculator.h"

RoadTripGraph::RoadTripGraph(string placesFileName, string stateFileName) {
    Parsing myParse;
    myParse.fillVector(placesFileName);
    myParse.fillNeighboringStates(stateFileName) ;
    locations = myParse.diffLocations;
}

void RoadTripGraph::createGraph()
{
    adjacencyMatrix.resize(locations.size(), vector<double>(locations.size()));
    adjacencyList.resize(locations.size(), vector<Parsing::Location *>());

    for (size_t x = 0; x < locations.size(); x++)
    {
        for (size_t y = 0; y < locations.size(); y++)
        {

            if ((checkNeighbor(locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state) && locations[x].name != locations[y].name)
            {
                adjacencyMatrix[x][y] = Calculator::calculateDistance(locations[x].latitude, locations[x].longitude,
                                                                      locations[y].latitude, locations[y].longitude);
                adjacencyList[x].push_back(&locations[y]);
            }
            else
            {
                adjacencyMatrix[x][y] = -1;
                adjacencyList[x].push_back(nullptr);
            }
        }
    }
}

bool RoadTripGraph::checkNeighbor(string name, vector<string> neighbors) {
    for (string n: neighbors) {
        if (name == n) {
            return true;
        }
    }
    return false;
}

void RoadTripGraph::KruskalsMST()
{
    vector<vector<double> > weights = adjacencyMatrix;
    int V = weights[0].size();
    parent.resize(V);
    double mincost = 0; 

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edge_count = 0;
    while (edge_count < V-3)
    {
        double min = INT_MAX;
        int a = -1, b = -1;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (find(i) != find(j) && (weights[i][j] < min) && (weights[i][j] != -1))
                {
                    min = weights[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        printf("Edge %d:(%d, %d) cost:%f \n",
               edge_count++, a, b, min);
        mincost += min;
    }
    printf("\n Minimum cost= %f \n", mincost);
}

void RoadTripGraph::union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int RoadTripGraph::find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

#include "roadtripgraph.h"
#include "parsing.h"
#include "calculator.h"

RoadTripGraph::RoadTripGraph(string placesFileName, string stateFileName) {
    Parsing myParse;
    myParse.fillVector(placesFileName);
    myParse.fillNeighboringStates(stateFileName) ;
    locations = myParse.diffLocations;
}

void RoadTripGraph::createGraph() {
    adjacencyMatrix.resize(locations.size(), vector<double>(locations.size()));
    adjacencyList.resize(locations.size(), vector<Parsing::Location*>());

    for (size_t x = 0; x < locations.size(); x++) {
        for (size_t y = 0; y < locations.size(); y++) {
            
            
            if ((checkNeighbor(locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state)
            && locations[x].name != locations[y].name) {
                adjacencyMatrix[x][y] = Calculator::calculateDistance(locations[x].latitude, locations[x].longitude,
                                                                        locations[y].latitude, locations[y].longitude);
                adjacencyList[x].push_back(&locations[y]);
            } else {
                adjacencyMatrix[x][y] = -1;
                adjacencyList[x].push_back(nullptr)  ;
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

bool RoadTripGraph::isValidEdge(int u, int v, vector<bool> inMST){
    if (u == v)
        return false;
    if (inMST[u] == false && inMST[v] == false)
        return false;
    else if (inMST[u] == true && inMST[v] == true)
        return false;
    return true;
}

void RoadTripGraph::primMST(vector<vector<double> > weights)
{
    int V = weights[0].size() ;
    vector<bool> inMST(V,false);
    inMST[0] = true;
    int edge_count = 0, mincost = 0;

    while (edge_count < V - 1)
    {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (weights[i][j] < min && weights[i][j] != -1)
                {
                    if (RoadTripGraph::isValidEdge(i, j, inMST))
                    {
                        min = weights[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1)
        {
            printf("Edge %d:(%d, %d) cost: %d \n",
                   edge_count++, a, b, min);
            mincost = mincost + min;
            inMST[b] = inMST[a] = true;
        }
    }
    printf("\n Minimum cost= %d \n", mincost);
}

#include "roadtripgraph.h"
#include "parsing.h"
#include "calculator.h"
#include <iostream>

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

vector<Parsing::Location> RoadTripGraph::KruskalsMST()
{
    std::cout << "========================================================================= " << std::endl;
    std::cout << " The minimum spanning tree for the current attractions has the following edges" << std::endl;
    vector<Parsing::Location> VisitedPlaces;
    vector<bool> isVisited(adjacencyMatrix[0].size(),false);
    VisitedPlaces.push_back(locations[0]);
    isVisited[0]=true;

    vector<vector<double> > weights = adjacencyMatrix;
    int V = weights[0].size();
    parent.resize(V);
    double mincost = 0; 

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edge_count = 0;
    while (edge_count < V-1)
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
        if(!isVisited[a]){
            VisitedPlaces.push_back(locations[a]);
            isVisited[a]=true;
        }
        if (!isVisited[b])
        {
            VisitedPlaces.push_back(locations[b]);
            isVisited[b] = true;
        }

        mincost += min;
    }
    printf("\n The minumum distance in KM = %f \n", mincost);
    std::cout << "========================================================================= " << std::endl;
    return VisitedPlaces;
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

vector<Parsing::Location> RoadTripGraph::BFS(int start, int end) {
    vector<bool> visited(locations.size());

    vector<Parsing::Location> l;
    vector<Parsing::Location> p;
    vector<int> distance(locations.size());
    vector<int> pred(locations.size());

    for (size_t i = 0; i < locations.size(); i++) {
        visited[i] = false;
        distance[i] = -1;
        pred[i] = -1;
    }
    

    visited[start] = true;
    distance[start] = 0;

    l.push_back(locations[start]);
    p.push_back(locations[start]);

    while (!l.empty())
    {
        Parsing::Location t = l[0];
        l.erase(l.begin());

        // priority should just be priority of the one at the fron

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {

            if (adjacencyMatrix[i][priority] >= 0 && !visited[i])
            {
                visited[i] = true;
                distance[i] = distance[priority] + 1;
                pred[i] = priority;
                p.push_back(locations[i]);
                l.push_back(locations[i]);
            }
        }
    }

    vector<Parsing::Location> path;

    int num = end;
    
    while (pred[num] != -1) {
        path.insert(path.begin(), locations[num]);
        num = pred[num];
    }
    path.insert(path.begin(), locations[start]);

    return path;
}

void RoadTripGraph::printBFS(int start, int end) {
    string temp1 = locations[start].state ;
    string temp2 = locations[end].state;
    temp1.pop_back();
    temp2.pop_back();

    std::cout << " To get from " << temp1 << " to " << temp2 << " here is the route with the least attractions "<<std::endl;
    vector<Parsing::Location> path = BFS(start, end);
    static int counter = 1;
    for (Parsing::Location i: path)
    {
        std::stringstream ss;
        ss << counter;
        string str = ss.str();

        string temp = str + " -> " +  i.name + ", " + i.state + "\n" ;
        counter++;
        std::cout << temp; 
    }
    std::cout << "========================================================================= " << std::endl;
}

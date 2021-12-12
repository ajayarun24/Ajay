#include "../cs225/catch/catch.hpp"
#include "../parsing.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../roadtripgraph.h"
using ::RoadTripGraph;
using ::Parsing;

TEST_CASE("test_basic_fileio", "[fileio]")
{
    bool firstTest = true ;
    Parsing tester;
    tester.fillVector("data/CS225 final project data.csv");
    vector<Parsing::Location> temp = tester.diffLocations;
    int rows = 0;
    std::ifstream file("data/CS225 final project data.csv");
    string line;
    while (getline(file, line))
        rows++;

    file.close();
    if (!((int)temp.size() == rows)) { firstTest = false;}

    REQUIRE(firstTest);
    REQUIRE(temp.size()>0);
    REQUIRE(rows>0);
}

TEST_CASE("Test_Neighboring_States","[fileio]"){
    bool secondTest = true;
    Parsing tester;
    tester.fillVector("data/CS225 final project data.csv");
    tester.fillNeighboringStates("data/neighbors-states.csv");
    vector<Parsing::Location> temp = tester.diffLocations;

    for (Parsing::Location hi : temp)
    {
        for (string lol : hi.neighboringStates)
            if (lol == hi.state)
            {
                secondTest = false;
            }
    }
   REQUIRE(secondTest);
}

TEST_CASE("Test Dijkstra shortest path", "[fileio]")
{
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    bool firstTest = true;
    Parsing tester;
    vector<Parsing::Location> temp = tester.diffLocations;
    
    vector<Parsing::Location> minPath;
    minPath = graph.Dijkstra(1, 14).first;

    REQUIRE(minPath.size() == 7);
}
TEST_CASE("Test Dijkstra correct distance", "[fileio]")
{
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    bool firstTest = true;
    Parsing tester;
    vector<Parsing::Location> temp = tester.diffLocations;

    std::pair<vector<Parsing::Location>, double> minPath;
    minPath = graph.Dijkstra(1, 14);
    double testKM = minPath.second;

    REQUIRE(testKM >0);
}

TEST_CASE("Test creating AdjacencyMatrix", "[test matrix]") {
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    // Checks if each location of the adjacency matrix has its list of edges populated
    for (vector<double> l: graph.adjacencyMatrix) {
        REQUIRE(l.size() == graph.locations.size());
    }

    // Checks if locations don't have edges with themselves
    for (size_t i = 0; i < graph.locations.size(); i++) {
        REQUIRE(graph.adjacencyMatrix[i][i] == -1);
    } 

}

TEST_CASE("Test BFS", "[test bfs]") {
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    srand(time(0));

    int start = rand()%(graph.locations.size()+1);

    int end = rand()%(graph.locations.size()+1);

    vector<Parsing::Location> bfs = graph.BFS(start, end).first;

    REQUIRE(bfs.size() > 0);
    REQUIRE(bfs.size() < graph.locations.size());
}

TEST_CASE("Test kruskals algorithm","[MST]"){
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    vector<Parsing::Location> i = graph.KruskalsMST(false);
    REQUIRE(i.size() == (graph.locations.size()));
}

TEST_CASE("Draw map", "[Map]"){
    PNG original, final ;
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    vector<Parsing::Location> bfs = graph.BFS(0, 14).first;

    RoadTripGraph::drawImage(bfs);

    original.readFromFile("us_map.png");
    final.readFromFile("us_map1.png");

    REQUIRE(!(original == final));
}

TEST_CASE("Djstrikas vs BFS", "[Algorithms]")
{
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    double bfsDistance = graph.BFS(0, 14).second;
    double DjstrijasDistance = graph.Dijkstra(0, 14).second;

    REQUIRE(bfsDistance > 0);
    REQUIRE(DjstrijasDistance > 0);
    REQUIRE(DjstrijasDistance < bfsDistance);
}
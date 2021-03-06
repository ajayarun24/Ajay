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

TEST_CASE("Test_Neihboring_States","[fileio]"){
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

    REQUIRE(minPath.size() == 18);
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


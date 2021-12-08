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

TEST_CASE("Run input code", "[fileio"){
     RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
     graph.createGraph();
     vector<Parsing::Location> i = graph.KruskalsMST();
     graph.printBFS(14, 25);
     graph.printDijkstra(1, 14);
    //  PNG hi;
    //  hi.readFromFile("../us_map.png");
    //  std::cout << hi.width() << std::endl;
    //  RoadTripGraph::addLines(hi, i);

}

TEST_CASE("Test coordToPixel", "[fileio"){
     std::cout << Calculator::coordToPixel(119.54, 37.87).first << std::endl;
     std::cout << Calculator::coordToPixel(119.54, 37.87).second << std::endl;
     std::cout << Calculator::coordToPixel(87.62, 41.90).first << std::endl;
     std::cout << Calculator::coordToPixel(87.62, 41.90).second << std::endl;
     std::cout << Calculator::coordToPixel(80.13, 25.78).first << std::endl;
     std::cout << Calculator::coordToPixel(80.13, 25.78).second << std::endl;


}


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

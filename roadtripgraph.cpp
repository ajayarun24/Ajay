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

    /*for (Parsing::Location l: locations) {
        std::cout<<l.name<< " "<<std::endl;
        for (string neigh: l.neighboringStates) {
            std::cout<<neigh<<std::endl;
        }
        std::cout<<" "<<std::endl;
    }*/

    for (size_t x = 0; x < locations.size(); x++) {
        for (size_t y = 0; y < locations.size(); y++) {
            
            
            if ((checkNeighbor(locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state)
            && locations[x].name != locations[y].name) {
                adjacencyMatrix[x][y] = Calculator::calculateDistance(locations[x].latitude, locations[x].longitude,
                                                                        locations[y].latitude, locations[y].longitude);
                adjacencyList[x].push_back(&locations[y]);
            } else {
                adjacencyMatrix[x][y] = std::numeric_limits<int>::max();
                adjacencyList[x].push_back(nullptr);
            }
        }
    }
    for (int i = 60; i < 80; i++) {
        for (int y = 0; y < 98; y++) {
            std::cout<<adjacencyMatrix[i][y]<<" "<<locations[i].name<<" "<<locations[y].name<<std::endl;
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
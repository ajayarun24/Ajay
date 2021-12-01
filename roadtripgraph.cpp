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
            
            
            if (checkNeighbor((locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state)
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
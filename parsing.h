#pragma once 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using std::string;
using std::vector;
using std::fstream;
using std::ios;


class Parsing{
    public:

    struct Location
    {
        string name;
        double latitude, longitude;
        int costFactor, priority;
        string state;
        vector<string> neighboringStates;

        Location(string Name, double lat, double longi, int CostFactor, int Priotity, string StateN)
        {
            name = Name;
            latitude = lat;
            longitude = longi;
            costFactor = CostFactor;
            priority = Priotity;
            state = StateN;
        }
    };
    //Empty constructor doesnt do anything 
    Parsing();
    void fillVector(string PlaceFilename);
    void fillNeighboringStates(string StateFileName);
    vector<Location> diffLocations ;
};
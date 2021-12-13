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
        // Location struct contains the data we will use for each node of our dataset
        struct Location
        {
            string name;
            double latitude, longitude;
            int priority;
            string state;
            vector<string> neighboringStates;
            Location(string Name, double lat, double longi, int priorityR, string StateN)
            {
                name = Name;
                latitude = lat;
                longitude = longi;
                state = StateN;
                priority = priorityR;
            }
    };
    //Empty constructor doesnt do anything 
    Parsing();
    void fillVector(string PlaceFilename);
    void fillNeighboringStates(string StateFileName);
    vector<Location> diffLocations ;
};
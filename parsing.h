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


class parsing{
    public:

    struct location
    {
        string name;
        double latitude, longitude;
        int costFactor, priority;
        string state;
        vector<string> neighboringStates;

        location(string Name, double lat, double longi, int CostFactor, int Priotity, string StateN)
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
    parsing();
    ~parsing();
    void fillVector(string PlaceFilename);
    void fillNeihboringStates(string StateFileName);
    vector<location> * diffLocations ;
};
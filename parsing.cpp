#include "parsing.h"

using std::ifstream;
using std::cout;
using std::endl;
//Empty constructor 
Parsing::Parsing() { }

void Parsing::fillVector(string placesFileName){

    ifstream fin(placesFileName);
    
    if(!fin.is_open()){
        std::cout << "Failed to open File" << std::endl;
    }

    string name, latitude, longitude, state;
     
    int currPriority = 0;
    while(fin.good()){
        getline(fin, name,',');
        getline(fin, latitude, ',');
        getline(fin, longitude, ',');
        getline(fin, state, '\n');

        double lat = std::atof(latitude.c_str());
        double longi = std::atof(longitude.c_str());
 
        Location temp(name,lat,longi, currPriority, state);
        currPriority++;
        diffLocations.push_back(temp);
        
    }
    fin.close();
}

void Parsing::fillNeighboringStates(string filename){
    ifstream fin(filename);

    if (!fin.is_open())
        std::cout << "Failed to open File" << std::endl;
    string state, neighborstate;
    while (fin.good()){
        getline(fin, state, ',');
        getline(fin, neighborstate,'\n');
        string temp = state;
        state = state + "\r";
        for (std::vector<Location>::iterator it = diffLocations.begin(); it != diffLocations.end(); ++it){
            if ((*it).state == state || (*it).state == temp)
            {
                (*it).neighboringStates.push_back(neighborstate);
            }
        }
    }
    fin.close();

    diffLocations[diffLocations.size() - 1].state = diffLocations[diffLocations.size() - 1].state + '\r';
};
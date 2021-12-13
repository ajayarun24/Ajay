#include "parsing.h"

using std::ifstream;
using std::cout;
using std::endl;
//Empty constructor 
Parsing::Parsing() { }

void Parsing::fillVector(string placesFileName){

    ifstream fin(placesFileName);
    
    //Throw an error if the file cannot be opened 
    if(!fin.is_open()){
        std::cout << "Failed to open File" << std::endl;
    }

    string name, latitude, longitude, state;

    //Get each row one at a time and put the values that are seperated by a comma into variables 
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
    //Get the values of state and neihboring state
    while (fin.good()){
        getline(fin, state, ',');
        getline(fin, neighborstate,'\n');
        string temp = state;
        state = state + "\r";
        for (std::vector<Location>::iterator it = diffLocations.begin(); it != diffLocations.end(); ++it){
            // If the state value is the same as the current "Location" then add that states neihboring state to the back of the neighboring states vector
            if ((*it).state == state || (*it).state == temp)
            {
                (*it).neighboringStates.push_back(neighborstate);
            }
        }
    }
    fin.close();
    //The last item doesnt have /r at the end so for consistency it is added
    diffLocations[diffLocations.size() - 1].state = diffLocations[diffLocations.size() - 1].state + '\r';
};
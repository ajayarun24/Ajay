#include "parsing.h"

using std::ifstream;

//Empty constructor 
parsing::parsing() 
{ 
    diffLocations = new vector<location>() ;
}

parsing::~parsing(){
    delete diffLocations;
}

void parsing::fillVector(string placesFileName){

    ifstream fin(placesFileName);
    
    if(!fin.is_open()){
        std::cout << "Failed to open File" << std::endl;
    }

    string name, latitude, longitude, n,e,costFactor,prioity, state;
     

    while(fin.good()){
        getline(fin, name,',');
        getline(fin, latitude, ',');
        getline(fin, longitude, ',');
        getline(fin, costFactor, ',');       
        getline(fin, prioity, ',');
        getline(fin, state, '\n');

       // std::cout << latitude << std::endl;

        double lat = std::atof(latitude.c_str());
        double longi = std::atof(longitude.c_str());
        std::stringstream temp1(prioity);
        int x = 0;
        temp1 >> x;

        location temp(name,lat,longi,0,x,state);
        diffLocations->push_back(temp);
        
    }
    fin.close();
}

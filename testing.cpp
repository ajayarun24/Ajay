#include "testing.h"
#include "parsing.h"

using ::Parsing;

void testing::testParsing(){
    bool firstTest = true, secondTest = true;
    Parsing tester;
    tester.fillVector("data/CS225 final project data.csv");
    vector<Parsing::Location> temp = tester.diffLocations;
    int rows = 0;
    std::ifstream file("data/CS225 final project data.csv");
    string line;
    while (getline(file, line))
        rows++;

    file.close();
    if((int)temp.size() == rows)
        std::cout << "Correct Size for diffLocations" << std::endl;
    else{
        std::cout << "Wrong size for diffLocations " << std::endl;
        firstTest = false;
    }

    tester.fillNeighboringStates("data/neighbors-states.csv");

    temp = tester.diffLocations;

    for(Parsing::Location hi : temp){
        for (string lol : hi.neighboringStates)
            if (lol == hi.state)
            {
                secondTest = false;
            }   
    }
    if(secondTest)
        std::cout << "Neihboring states is filled for each location " << std::endl;
    else
        std::cout << "Neihboring states is not filled for each location " << std::endl;
    
    int total = secondTest + firstTest ;

    std::cout << total << " out of 2 tests passed" << std::endl;
}
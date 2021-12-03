#include <testing.h>
#include <parsing.h>

using ::Parsing;

void testing::testParsing(){
    Parsing tester;
    tester.fillVector("data / CS225 final project data.csv");
    vector<Parsing::Location> temp = tester.diffLocations;
    int rows = 0;
    std::ifstream file("data / CS225 final project data.csv");
    string line;
    while (getline(file, line))
        rows++;

    if(temp.size() == rows)
        std::cout << "Correct Size for diffLocations" << std::endl;
    else
        std::cout << "Wrong size for diffLocations " << std::endl;

}
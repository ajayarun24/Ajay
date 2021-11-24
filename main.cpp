#include "someprogram.h"
#include <iostream>

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

using std::string;
using std::vector;
using std::pair;
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<int> {}});
        }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        
        // Extract each integer
        while(ss >> val){
            
            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);
            
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}

struct location
{
    string name;
    long latitude, longitude;
    bool n,e;
    int costFactor, priority;
    string state;
    vector<string> neighboringStates ;
    
    location(string Name, long lat, long longi, bool N, bool E, int CostFactor, int Priotity, string State){
        name = Name;
        latitude = lat;
        longitude= longi;
        n = N;
        e = E;
        costFactor = CostFactor;
        priority = Priotity;
        state = State;
    }
    
};

int main() {
    // Read three_cols.csv and ones.csv
    std::vector<std::pair<std::string, std::vector<int> > > test_read = read_csv("data/CS225 final project data.csv");

    pair<string,vector<int> > tester = test_read[1];
    std::cout << tester.first << std::endl;
    return 0;
}


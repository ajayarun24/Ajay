#include "bfs.h"

BreadthFirstSearch::BreadthFirstSearch(vector<vector<double>> aM,vector<vector<Parsing::Location*>> aL,
    vector<Parsing::Location> l) {
        adjacencyMatrix = aM;
        adjacencyList = aL;
        locations = l;
    }

vector<Parsing::Location> BreadthFirstSearch::doBFS(int start) {
    vector<bool> visited(locations.size());

    vector<Parsing::Location> l;

    for (bool v: visited) {
        v = false;
    }
    
    visited[start] = true;

    l.push_back(locations[start]);

    while (!l.empty()) {
        Parsing::Location t = l[0];
        l.erase(l.begin());

        for (size_t i = 0; i < adjacencyMatrix[t.priority - 1].size(); i++) {
            if (adjacencyMatrix[t.priority - 1][i] > 0 && !visited[i]) {
                l.push_back(locations[i]);
                visited[i] = true;
            }
        }
    }
    return l;
}
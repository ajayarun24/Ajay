#include "bfs.h"

BreadthFirstSearch::BreadthFirstSearch(vector<vector<double> > aM, vector<vector<Parsing::Location *> > aL,
                                       vector<Parsing::Location> l)
{
    adjacencyMatrix = aM;
    adjacencyList = aL;
    locations = l;
}

vector<Parsing::Location> BreadthFirstSearch::doBFS(int start)
{
    vector<bool> visited(locations.size());

    vector<Parsing::Location> l;
    vector<Parsing::Location> p;

    for (bool v : visited)
    {
        v = false;
    }

    visited[start] = true;

    l.push_back(locations[start]);
    p.push_back(locations[start]);

    while (!l.empty())
    {
        Parsing::Location t = l[0];
        l.erase(l.begin());

        // priority should just be priority of the one at the fron

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {

            if (adjacencyMatrix[i][priority] >= 0 && !visited[i])
            {
                p.push_back(locations[i]);
                l.push_back(locations[i]);
                visited[i] = true;
            }
        }
    }

    return p;
}
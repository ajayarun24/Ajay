#include <map>
#include <queue>
#include <string>
#include <vector>
#include "DijstrikasAlgorithm.h"

using namespace std;

Graph::Graph(int V)
{
    this->vertices = vertices;
    adj = new list<integerPair> [vertices];
}
  
void Graph::addEdge(int u, int graphVertices, int weight)
{
    adj[u].push_back(make_pair(graphVertices, weight));
    adj[graphVertices].push_back(make_pair(u, weight));
}

void Graph::shortestPath(int source)
{
    priority_queue< integerPair, vector <integerPair> , greater<integerPair> > priorityQ;
  
    vector<int> dist(vertices, INF);
    // Insert source itself in priority queue and initialize its distance as 0.
    pq.push(make_pair(0, source));
    dist[source] = 0;
  

    while (!priorityQ.empty())
    {

        int u = priorityQ.top().second;
        priorityQ.pop();
  
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {

            int vOne = (*i).first;
            int graphWeight = (*i).second;
  
            //  If there is shorted path to vOne through u.
            if (dist[vOne] > dist[u] + graphWeight)
            {
                // Updating distance of vOne
                dist[vOne] = dist[u] + graphWeight;
                priorityQ.push(make_pair(dist[vOne], vOne));
            }
        }
    }
  
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < graphVertices; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}


vector<IDK> Dijkstra(const vector<IDK>& USmap, string beginning, bool set[]) {
    if(beginning = "AL" || beginning = "HA"){
        return vector<IDK>();
    }
    vector<IDK> returnPoint;
        State* current;
         map<string, bool> visited;
    map<string, State*> predecessor;
    map<string, double> distance;
    for (Iterator::it = states.begin(); it != states.end(); ++it) {
        distance[(*it)->getName()] = DBL_MAX;                      
        predecessor[(*it)->getName()] = NULL;
        visited[(*it)->getName()] = false;
    }
   distance[start] = 0;
    predecessor[start] = NULL;
    visited[start] = true
    for (Iterator::it = distance.begin(); it != distance.end(); ++it) {
        q.push(*it);  
    }

    while (!q.empty()) {
        if (q.top().second != distance[q.top().first]) 
        {
            q.pop();
            continue;
        }
        returnPoint.push_back(new IDK(q.top().first, q.top().second));
        current = returnPoint[returnPoint.size() - 1];
        current->addBorder(newEdge); 
        q.pop();  
        visited[current->getName()] = true; 

        for (Iterator::it = states.begin(); it != states.end(); ++it)
        {
            if ((*it)->getName() == current->getName()) {
                borders = (*it)->getBorders();
                break;
            }
        }
    }

    return returnPoint;
}
    }
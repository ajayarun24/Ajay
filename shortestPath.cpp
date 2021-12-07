using namespace std;

//creates the edges between two vertices of input points source and destination
void minPath::add_edge(vector<vector<Parsing::Location*>> adj int src, int dest)
{
    adjacencyMatrix= adj;
    source= src;
    dest= destination;
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
// find Index of input points in adjacency matrix
// figure out corresponding states and rows
// in each row, find the distance to the neighboring, rest will 0
// for each state have distance in matrix, not neighbors= infinite distance
//then implement dijkstra
//While doing dijkstras find the path as you go
void minPath::printShortestDistance(vector<vector<Parsing::Location*>> adj, int s, int dest, int v){
    //checking for valid starting and ending point inputs
    if(doBFS( --- INPUT ONCE BFS.CPP HAS BEEN CHANGED) == false){
        cout << "Hawaii and Alaska are not considered valid inputs as a road trip there from with in the continental United States
        isn't impossible. Please try again and make sure you type in the correct state code and that HA or AK aren't your start/end points" << endl;
        return ;
    }
    //create a vector that holds which states need to be traversed in sequence along the shortest path
    vector<Parsing::Location> path;
    int statesOnPath= dest;
    path.push_back(statesOnPath);
    int pred[v], dist[v];
    while(pred[statesOnPath]!= -1){
        path.push_back(pred[statesOnPath]);
        statesOnPath = pred[statesOnPath];
    }
    cout << "shortest path length between these input points is " << dist[dest] << endl;
    cout << "\nPath is::\n" << endl;
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}
}
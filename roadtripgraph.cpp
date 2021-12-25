#include "roadtripgraph.h"
#include "calculator.h"
#include <iostream>
using ::Calculator;


RoadTripGraph::RoadTripGraph(string placesFileName, string stateFileName) {
    Parsing myParse;
    myParse.fillVector(placesFileName);
    myParse.fillNeighboringStates(stateFileName) ;
    // Parses locations and sets local variable
    locations = myParse.diffLocations;
}

void RoadTripGraph::createGraph()
{
    adjacencyMatrix.resize(locations.size(), vector<double>(locations.size()));
    adjacencyList.resize(locations.size(), vector<Parsing::Location *>());

    for (size_t x = 0; x < locations.size(); x++)
    {
        for (size_t y = 0; y < locations.size(); y++)
        {
            // Checks if attractions should have edge between them
            if ((checkNeighbor(locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state) && locations[x].name != locations[y].name)
            {
                adjacencyMatrix[x][y] = Calculator::calculateDistance(locations[x].latitude, locations[x].longitude,
                                                                      locations[y].latitude, locations[y].longitude);
                adjacencyList[x].push_back(&locations[y]);
            }
            else
            {
                // If not pushes default values
                adjacencyMatrix[x][y] = -1;
                adjacencyList[x].push_back(nullptr);
            }
        }
    }
}

bool RoadTripGraph::checkNeighbor(string name, vector<string> neighbors) {
    // Checks if attraction is neighbor to other
    for (string n: neighbors) {
        if (name == n) {
            return true;
        }
    }
    return false;
}

vector<Parsing::Location> RoadTripGraph::KruskalsMST(bool shouldPrint)
{
    if(shouldPrint){
    std::cout << "========================================================================= " << std::endl;
    std::cout << "The minimum spanning tree for the current attractions has the following edges:" << std::endl;
    }
    vector<Parsing::Location> VisitedPlaces;
    vector<bool> isVisited(adjacencyMatrix[0].size(),false);

    //Grab our adjcaceny matrix and store a local copy of it
    vector<vector<double> > weights = adjacencyMatrix;
    int V = weights[0].size();
    //Parent is our disjoint set
    parent.resize(V);
    double mincost = 0; 

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edge_count = 0;
    while (edge_count < V-1)
    //While we have one less edge than the number of vertices
    {
        double min = INT_MAX;
        int a = -1, b = -1;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                //If the edge is our lowest value and they are not connecting the same node then store the coordinates of it 
                if (find(i) != find(j) && (weights[i][j] < min) && (weights[i][j] != -1))
                {
                    min = weights[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        //Union the two nodes to check for cycle detection
        union1(a, b);
        //Pring the edge
        if(shouldPrint){
        printf("Edge %d:(%d, %d) cost:%f \n",
               edge_count, a, b, min);
        }
        edge_count++;

        //We want to maintain a vector of each of the nodes in case we want to show it on a map
        if(!isVisited[a]){
            VisitedPlaces.push_back(locations[a]);
            isVisited[a]=true;
        }
        if (!isVisited[b])
        {
            VisitedPlaces.push_back(locations[b]);
            isVisited[b] = true;
        }
        //Increase the min cost for the spanning tree
        mincost += min;
    }
    if(shouldPrint){
    printf("The minumum distance in KM = %f \n", mincost);
    std::cout << "========================================================================= " << std::endl;
    }
    return VisitedPlaces;
}

void RoadTripGraph::union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int RoadTripGraph::find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

std::pair<vector<Parsing::Location>, double> RoadTripGraph::BFS(int start, int end) {

    // Vectors to store information
    vector<bool> visited(locations.size());

    vector<Parsing::Location> l;
    vector<Parsing::Location> p;
    vector<int> distance(locations.size());
    vector<int> pred(locations.size());

    // Sets defaults
    for (size_t i = 0; i < locations.size(); i++) {
        visited[i] = false;
        distance[i] = -1;
        pred[i] = -1;
    }
    
    // Starts at starting node
    visited[start] = true;
    distance[start] = 0;

    l.push_back(locations[start]);
    p.push_back(locations[start]);

    while (!l.empty())
    {
        // Takes front of queue then deletes
        Parsing::Location t = l[0];
        l.erase(l.begin());

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {

            // Adds adjacent vertices
            if (adjacencyMatrix[i][priority] >= 0 && !visited[i])
            {
                visited[i] = true;
                distance[i] = distance[priority] + 1;
                pred[i] = priority;
                p.push_back(locations[i]);
                l.push_back(locations[i]);
            }
        }
    }

    vector<Parsing::Location> path;

    int num = end;

    double dist = 0;

    // Goes through predecessors to find path
    while (pred[num] != -1) {
        path.insert(path.begin(), locations[num]);
        dist+= adjacencyMatrix[num][pred[num]];
        num = pred[num];
    }
    path.insert(path.begin(), locations[start]);

    // Returns path and distance
    std::pair<vector<Parsing::Location>, double> f = std::make_pair(path, dist);
    return f;
}

void RoadTripGraph::printBFS(int start, int end) {
    string temp1 = locations[start].state ;
    string temp2 = locations[end].state;
    temp1.pop_back();
    temp2.pop_back();


    // Prints attractions in BFS, along with distance
    std::cout << "To get from " << temp1 << " to " << temp2 << " here is the route while using BFS:"<<std::endl;
    std::pair<vector<Parsing::Location>, double> b = BFS(start,end);
    vector<Parsing::Location> path = b.first;
    static int counter = 1;
    for (Parsing::Location i: path)
    {
        std::stringstream ss;
        ss << counter;
        string str = ss.str();

        string temp = str + " -> " +  i.name + ", " + i.state + "\n" ;
        counter++;
        std::cout << temp; 
    }
    std::cout<<b.second<<" KM to "<<locations[end].name<<std::endl;
    std::cout << "========================================================================= " << std::endl;
}

std::pair<vector<Parsing::Location>, double> RoadTripGraph::Dijkstra(int start, int end) {

    // Vectors to store information
    vector<double> weights(locations.size());
    vector<int> pred(locations.size());
    vector<Parsing::Location> q;
    vector<Parsing::Location> span;
    vector<bool> visited(locations.size());

    // Sets vectors to default values
    for (size_t i = 0; i < locations.size(); i++) {
        visited[i] = false;
        weights[i] = std::numeric_limits<double>::max();;
        pred[i] = -1;
    }



    q.push_back(locations[start]);
    span.push_back(locations[start]);

    // Starts at start node
    visited[start] = true;
    weights[start] = 0;

    while (!q.empty()) {
        // Takes front of spanning set then erases
        Parsing::Location t = q[0];
        
        q.erase(q.begin());

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {
            // Checks adjacent vertices, and updates distances relative to start accordingly
            if (adjacencyMatrix[i][priority] >= 0 && !visited[i])
            {
                if (weights[i] > adjacencyMatrix[i][priority] + weights[priority])
                {
                    weights[i] = adjacencyMatrix[i][priority] + weights[priority];
                    pred[i] = priority;
                }
            }
        }


        double lowest = std::numeric_limits<double>::max();
        double ind = 0;
        
        // Finds lowest edge weight among those not in spanning set, and adds to spanning set
        for ( Parsing::Location  l : locations) {
            if (visited[l.priority] == false) {
                if (weights[l.priority] < lowest) {
                    lowest = weights[l.priority];
                    ind = l.priority;
                }
            }
        }
        visited[ind] = true;
        span.push_back(locations[ind]);

        q.push_back(locations[ind]);

        // Breaks once last point is visited
        if (visited[end]) break;
    }

    vector<Parsing::Location> path;

    

    int num = end;

    // Goes through predecessors to find path
    while (pred[num] != -1) {
        path.insert(path.begin(), locations[num]);
        num = pred[num];
    }
    path.insert(path.begin(), locations[start]);

    std::pair<vector<Parsing::Location>, double> toReturn = std::make_pair(path, weights[end]);

    return toReturn;
}
//Testing remote
void RoadTripGraph::printDijkstra(int start, int end) {
    std::pair<vector<Parsing::Location>, double> p = Dijkstra(start, end);

    string temp1 = locations[start].state;
    string temp2 = locations[end].state;
    temp1.pop_back();
    temp2.pop_back();

    // Prints order of Dijkstra's along with distance traveled

    std::cout << "To get from " << temp1 << " to " << temp2 << " here is the route with the Dijkstra's algorithm:" << std::endl;

    static int counter = 1;
    for (Parsing::Location i : p.first)
    {
        std::stringstream ss;
        ss << counter;
        string str = ss.str();

        string temp = str + " -> " + i.name + ", " + i.state + "\n";
        counter++;
        std::cout << temp;
    }
    std::cout<<p.second<<" KM to "<<locations[end].name<<std::endl;
}

PNG RoadTripGraph::addPoints(PNG image, std::vector<Parsing::Location> attractions)
{
    HSLAPixel myPixel1 = HSLAPixel(360, 0.8, 0.5);
    for (size_t i = 0; i < attractions.size(); i++) //loop through all attractions along the way
    {
        double lat = attractions[i].latitude; //extract latitude attraction
        double longi = attractions[i].longitude; //extract longitude attraction
        int radius = 20;
        for (int y = -radius; y <= radius; y++)
        {
            for (int x = -radius; x <= radius; x++)
            {
                if ((x * x + y * y) <= radius * radius) //only pixels within a circle of radius 20 will change color. Useful for plotting a circle at each destination
                {
                    HSLAPixel &pixel = image.getPixel(Calculator::coordToPixel(longi, lat).first + x, Calculator::coordToPixel(longi, lat).second + y);
                    pixel = myPixel1;
                }
            }
        }
    }
    return image;
}

    // draws a line between two destinations by determining slope between two points
void RoadTripGraph::addLines(PNG image, std::vector<Parsing::Location> attractions)
{
    HSLAPixel myPixel2 = HSLAPixel(360, 0.8, 0.0);
    for (size_t i = 0; i < attractions.size() - 1; i++)
    {
        double point1_lat = attractions[i].latitude;
        double point1_longi = attractions[i].longitude;
        double point1_x = (Calculator::coordToPixel(point1_longi, point1_lat)).first;
        double point1_y = (Calculator::coordToPixel(point1_longi, point1_lat)).second;
        HSLAPixel &pixel1 = image.getPixel(point1_x, point1_y);
        pixel1 = myPixel2;
        double point2_lat = attractions[i + 1].latitude;
        double point2_longi = attractions[i + 1].longitude;
        double point2_x = (Calculator::coordToPixel(point2_longi, point2_lat)).first;
        double point2_y = (Calculator::coordToPixel(point2_longi, point2_lat)).second;
        HSLAPixel &pixel2 = image.getPixel(point2_x, point2_y);
        pixel2 = myPixel2;
        double slope = (point2_y - point1_y) / (point2_x - point1_x);
        if (point1_x < point2_x) //moving east from point1 to point 2
        {
            for (unsigned x = point1_x; x <= point2_x; x++)
            {
                HSLAPixel &pixel3 = image.getPixel(x, (point1_y + (slope * (x - point1_x))));
                pixel3 = myPixel2;
                for (int i = 1; i < 4; i++) { //adds thickness to the line between 2 points
                    HSLAPixel &p = image.getPixel(x, (point1_y + (slope * (x - point1_x) + i)));
                    HSLAPixel &o = image.getPixel(x, (point1_y + (slope * (x - point1_x) - i)));
                    p = myPixel2;
                    o = myPixel2;
                }
            }
        }
        if (point1_x > point2_x) //moving west from point1 to point2
        {
            for (unsigned x = point1_x; x >= point2_x; x--)
            {
                HSLAPixel &pixel3 = image.getPixel(x, (point1_y + (slope * (x - point1_x))));
                pixel3 = myPixel2;
                for (int i = 1; i < 4; i++) {
                    HSLAPixel &p = image.getPixel(x, (point1_y + (slope * (x - point1_x) + i)));
                    HSLAPixel &o = image.getPixel(x, (point1_y + (slope * (x - point1_x) - i)));
                    p = myPixel2;
                    o = myPixel2;
                }
            }
        }
        if (point1_x == point2_x)
        {
            if (point1_y < point2_y) //moving south from point1 to point2
            {
                for (unsigned y = point1_y; y <= point2_y; y++)
                {
                    HSLAPixel &pixel3 = image.getPixel(point1_x, y);
                    pixel3 = myPixel2;
                    for (int i = 1; i < 4; i++) {
                        HSLAPixel &p = image.getPixel(point1_x + i, y);
                        HSLAPixel &o = image.getPixel(point1_x - i, y);
                        p = myPixel2;
                        o = myPixel2;
                    }
                }
            }
            if (point1_y > point2_y) //moving north from point1 to point2
            {
                for (unsigned y = point1_y; y >= point2_y; y--)
                {
                    HSLAPixel &pixel3 = image.getPixel(point1_x, y);

                    
                    pixel3 = myPixel2;
                    for (int i = 1; i < 4; i++) {
                        HSLAPixel &p = image.getPixel(point1_x + i, y);
                        HSLAPixel &o = image.getPixel(point1_x - i, y);
                        p = myPixel2;
                        o = myPixel2;
                    }
                }
            }
        }
    }
    image.writeToFile("us_map1.png");
}

void RoadTripGraph::drawImage(std::vector<Parsing::Location> attractions){
    //Read the us map and then call the draw function in the right order 
    PNG hi;
    hi.readFromFile("us_map.png");
    //we want to add points first and then lines
    RoadTripGraph::addLines(RoadTripGraph::addPoints(hi, attractions), attractions);
}

void RoadTripGraph::runProgram(){
    // Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();
    //Poll for a starting state and ending state
    string startingState, endingState;
    int startIdx, endIdx;
    std::cout << "Enter a starting state: " << std::endl;
    std::cin >> startingState;
    std::cout << "Enter an ending state: " << std::endl;
    std::cin >> endingState;
    //Out states in each struct has \r at the end so we add it on here
    startingState += "\r";
    endingState += "\r";
    //Seed rand
    srand(time(0));
    vector<int> locationsStartIdx, locationEndIdx;

    //Select a random attraction in the starting and ending state 
    for (Parsing::Location i : graph.locations)
    {
        if (i.state == startingState)
            locationsStartIdx.push_back(i.priority);
        if (i.state == endingState)
            locationEndIdx.push_back(i.priority);
    }
    //If nothing was found then the state they inputed doesnt exist
    if (locationEndIdx.size() == 0 || locationsStartIdx.size() == 0)
    {
        std::cout << "Your inputs were not states!" << std::endl;
    }
    else
    {
        startIdx = locationsStartIdx[rand() % locationsStartIdx.size()];
        endIdx = locationEndIdx[rand() % locationEndIdx.size()];
        //Call our three algorithms
        vector<Parsing::Location> i = graph.KruskalsMST(true);
        vector<Parsing::Location> bfs = graph.BFS(startIdx, endIdx).first;
        vector<Parsing::Location> djstrikasResult = graph.Dijkstra(startIdx,endIdx).first;
        //Print the ones that have a seperate pring function 
        graph.printBFS(startIdx, endIdx);
        graph.printDijkstra(startIdx, endIdx);
        std::cout << "===========================================================================" << std::endl;

        string graph;
        //Prompt the user to see what path they want to graphically see
        std::cout << "If you would like to see the path with Dijkstra's press 1.  \nIf you want to see the path with BFS press any other key." << std::endl;
        std::cin >> graph;

        //Based on what they pick call our drawing function with the respective vector of type location
        if(graph == "1"){
            RoadTripGraph::drawImage(djstrikasResult);
        }
        else{
            RoadTripGraph::drawImage(bfs);
        }
            std::cout << "Check us_map1.png for your path." << std::endl;
        
    }
}

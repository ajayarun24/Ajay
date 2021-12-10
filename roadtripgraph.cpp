#include "roadtripgraph.h"
#include "calculator.h"
#include <iostream>
using ::Calculator;


RoadTripGraph::RoadTripGraph(string placesFileName, string stateFileName) {
    Parsing myParse;
    myParse.fillVector(placesFileName);
    myParse.fillNeighboringStates(stateFileName) ;
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

            if ((checkNeighbor(locations[x].state, locations[y].neighboringStates) || locations[x].state == locations[y].state) && locations[x].name != locations[y].name)
            {
                adjacencyMatrix[x][y] = Calculator::calculateDistance(locations[x].latitude, locations[x].longitude,
                                                                      locations[y].latitude, locations[y].longitude);
                adjacencyList[x].push_back(&locations[y]);
            }
            else
            {
                adjacencyMatrix[x][y] = -1;
                adjacencyList[x].push_back(nullptr);
            }
        }
    }
}

bool RoadTripGraph::checkNeighbor(string name, vector<string> neighbors) {
    for (string n: neighbors) {
        if (name == n) {
            return true;
        }
    }
    return false;
}

vector<Parsing::Location> RoadTripGraph::KruskalsMST()
{
    std::cout << "========================================================================= " << std::endl;
    std::cout << "The minimum spanning tree for the current attractions has the following edges:" << std::endl;
    vector<Parsing::Location> VisitedPlaces;
    vector<bool> isVisited(adjacencyMatrix[0].size(),false);

    vector<vector<double> > weights = adjacencyMatrix;
    int V = weights[0].size();
    parent.resize(V);
    double mincost = 0; 

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edge_count = 0;
    while (edge_count < V-1)
    {
        double min = INT_MAX;
        int a = -1, b = -1;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (find(i) != find(j) && (weights[i][j] < min) && (weights[i][j] != -1))
                {
                    min = weights[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        printf("Edge %d:(%d, %d) cost:%f \n",
               edge_count++, a, b, min);
        if(!isVisited[a]){
            VisitedPlaces.push_back(locations[a]);
            isVisited[a]=true;
        }
        if (!isVisited[b])
        {
            VisitedPlaces.push_back(locations[b]);
            isVisited[b] = true;
        }

        mincost += min;
    }
    printf("The minumum distance in KM = %f \n", mincost);
    std::cout << "========================================================================= " << std::endl;
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
    vector<bool> visited(locations.size());

    vector<Parsing::Location> l;
    vector<Parsing::Location> p;
    vector<int> distance(locations.size());
    vector<int> pred(locations.size());

    for (size_t i = 0; i < locations.size(); i++) {
        visited[i] = false;
        distance[i] = -1;
        pred[i] = -1;
    }
    

    visited[start] = true;
    distance[start] = 0;

    l.push_back(locations[start]);
    p.push_back(locations[start]);

    while (!l.empty())
    {
        Parsing::Location t = l[0];
        l.erase(l.begin());

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {

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

    int dist =0;
    
    while (pred[num] != -1) {
        path.insert(path.begin(), locations[num]);
        dist+= adjacencyMatrix[num][pred[num]];
        num = pred[num];
    }
    dist+= adjacencyMatrix[num][pred[num]];
    path.insert(path.begin(), locations[start]);

    std::pair<vector<Parsing::Location>, double> f = std::make_pair(path, dist);
    return f;
}

void RoadTripGraph::printBFS(int start, int end) {
    string temp1 = locations[start].state ;
    string temp2 = locations[end].state;
    temp1.pop_back();
    temp2.pop_back();

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

    vector<double> weights(locations.size());
    vector<int> pred(locations.size());
    vector<Parsing::Location> q;
    vector<Parsing::Location> span;
    vector<bool> visited(locations.size());

    for (size_t i = 0; i < locations.size(); i++) {
        visited[i] = false;
        weights[i] = std::numeric_limits<double>::max();;
        pred[i] = -1;
    }



    q.push_back(locations[start]);
    span.push_back(locations[start]);

    visited[start] = true;
    weights[start] = 0;

    while (!q.empty()) {
        Parsing::Location t = q[0];

        
        q.erase(q.begin());

        size_t priority = t.priority;

        for (size_t i = 0; i < locations.size(); i++)
        {

            if (adjacencyMatrix[i][priority] >= 0 && !visited[i])
            {
                
                weights[i] = adjacencyMatrix[i][priority] + weights[priority];
                pred[i] = priority;
            }
        }


        double lowest = std::numeric_limits<double>::max();
        double ind = 0;

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

        if (visited[end]) break;
    }

    vector<Parsing::Location> path;

    

    int num = end;
    
    while (pred[num] != -1) {
        path.insert(path.begin(), locations[num]);
        num = pred[num];
    }
    path.insert(path.begin(), locations[start]);

    std::pair<vector<Parsing::Location>, double> toReturn = std::make_pair(path, weights[end]);

    return toReturn;
}

void RoadTripGraph::printDijkstra(int start, int end) {
    std::pair<vector<Parsing::Location>, double> p = Dijkstra(start, end);

    string temp1 = locations[start].state;
    string temp2 = locations[end].state;
    temp1.pop_back();
    temp2.pop_back();

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
    HSLAPixel *myPixel1 = new HSLAPixel(360, 0.8, 0.5);
    for (size_t i = 0; i < attractions.size(); i++)
    {
        double lat = attractions[i].latitude;
        double longi = attractions[i].longitude;
        int radius = 20;
        for (int y = -radius; y <= radius; y++)
        {
            for (int x = -radius; x <= radius; x++)
            {
                if ((x * x + y * y) <= radius * radius)
                {
                    HSLAPixel &pixel = image.getPixel(Calculator::coordToPixel(longi, lat).first + x, Calculator::coordToPixel(longi, lat).second + y);
                    pixel = *myPixel1;
                }
            }
        }
    }
    return image;
}

void RoadTripGraph::addLines(PNG image, std::vector<Parsing::Location> attractions)
{
    HSLAPixel *myPixel2 = new HSLAPixel(360, 0.8, 0.0);
    for (size_t i = 0; i < attractions.size() - 1; i++)
    {
        double point1_lat = attractions[i].latitude;
        double point1_longi = attractions[i].longitude;
        double point1_x = (Calculator::coordToPixel(point1_longi, point1_lat)).first;
        double point1_y = (Calculator::coordToPixel(point1_longi, point1_lat)).second;
        HSLAPixel &pixel1 = image.getPixel(point1_x, point1_y);
        pixel1 = *myPixel2;
        double point2_lat = attractions[i + 1].latitude;
        double point2_longi = attractions[i + 1].longitude;
        double point2_x = (Calculator::coordToPixel(point2_longi, point2_lat)).first;
        double point2_y = (Calculator::coordToPixel(point2_longi, point2_lat)).second;
        HSLAPixel &pixel2 = image.getPixel(point2_x, point2_y);
        pixel2 = *myPixel2;
        double slope = (point2_y - point1_y) / (point2_x - point1_x);
        if (point1_x < point2_x)
        {
            for (unsigned x = point1_x; x <= point2_x; x++)
            {
                HSLAPixel &pixel3 = image.getPixel(x, (point1_y + (slope * (x - point1_x))));
                pixel3 = *myPixel2;
                for (int i = 1; i < 4; i++) {
                    HSLAPixel &p = image.getPixel(x, (point1_y + (slope * (x - point1_x) + i)));
                    HSLAPixel &o = image.getPixel(x, (point1_y + (slope * (x - point1_x) - i)));
                    p = *myPixel2;
                    o = *myPixel2;
                }
            }
        }
        if (point1_x > point2_x)
        {
            for (unsigned x = point1_x; x >= point2_x; x--)
            {
                HSLAPixel &pixel3 = image.getPixel(x, (point1_y + (slope * (x - point1_x))));
                pixel3 = *myPixel2;
                for (int i = 1; i < 4; i++) {
                    HSLAPixel &p = image.getPixel(x, (point1_y + (slope * (x - point1_x) + i)));
                    HSLAPixel &o = image.getPixel(x, (point1_y + (slope * (x - point1_x) - i)));
                    p = *myPixel2;
                    o = *myPixel2;
                }
            }
        }
        if (point1_x == point2_x)
        {
            if (point1_y < point2_y)
            {
                for (unsigned y = point1_y; y <= point2_y; y++)
                {
                    HSLAPixel &pixel3 = image.getPixel(point1_x, y);
                    pixel3 = *myPixel2;
                    for (int i = 1; i < 4; i++) {
                        HSLAPixel &p = image.getPixel(point1_x + i, y);
                        HSLAPixel &o = image.getPixel(point1_x - i, y);
                        p = *myPixel2;
                        o = *myPixel2;
                    }
                }
            }
            if (point1_y > point2_y)
            {
                for (unsigned y = point1_y; y >= point2_y; y--)
                {
                    HSLAPixel &pixel3 = image.getPixel(point1_x, y);

                    
                    pixel3 = *myPixel2;
                    for (int i = 1; i < 4; i++) {
                        HSLAPixel &p = image.getPixel(point1_x + i, y);
                        HSLAPixel &o = image.getPixel(point1_x - i, y);
                        p = *myPixel2;
                        o = *myPixel2;
                    }
                }
            }
        }
    }
    image.writeToFile("us_map1.png");
}

void RoadTripGraph::drawImage(std::vector<Parsing::Location> attractions){
    PNG hi;
    hi.readFromFile("us_map.png");
    RoadTripGraph::addLines(RoadTripGraph::addPoints(hi, attractions), attractions);
}

void RoadTripGraph::runProgram(){
    // Make a graph
    RoadTripGraph graph("data/CS225 final project data.csv", "data/neighbors-states.csv");
    graph.createGraph();

    string startingState, endingState;
    int startIdx, endIdx;
    std::cout << "Enter a starting state: " << std::endl;
    std::cin >> startingState;
    std::cout << "Enter an ending state: " << std::endl;
    std::cin >> endingState;

    

    startingState += "\r";
    endingState += "\r";
    srand(time(0));
    vector<int> locationsStartIdx, locationEndIdx;

    for (Parsing::Location i : graph.locations)
    {
        if (i.state == startingState)
            locationsStartIdx.push_back(i.priority);
        if (i.state == endingState)
            locationEndIdx.push_back(i.priority);
    }
    if (locationEndIdx.size() == 0 || locationsStartIdx.size() == 0)
    {
        std::cout << "Your inputs were not states!" << std::endl;
    }
    else
    {
        startIdx = locationsStartIdx[rand() % locationsStartIdx.size()];
        endIdx = locationEndIdx[rand() % locationEndIdx.size()];
        vector<Parsing::Location> i = graph.KruskalsMST();
        vector<Parsing::Location> bfs = graph.BFS(startIdx, endIdx).first;
        vector<Parsing::Location> djstrikasResult = graph.Dijkstra(startIdx,endIdx).first;
        graph.printBFS(startIdx, endIdx);
        graph.printDijkstra(startIdx, endIdx);
        std::cout << "===========================================================================" << std::endl;

        string graph;
        std::cout << "If you would like to see the path with Dijkstra's press 1.  \nIf you want to see the path with BFS press any other key." << std::endl;
        std::cin >> graph;

        if(graph == "1"){
            RoadTripGraph::drawImage(djstrikasResult);
        }
        else{
            RoadTripGraph::drawImage(bfs);
        }
            std::cout << "Check us_map1.png for your path." << std::endl;
        
    }
}

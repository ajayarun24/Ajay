#include<bits/stdc++.h>
#pragma once

using namespace std;


class Graph{
    public:
    Graph(int vertices);
    void addEdge(int u, int graphVertices, int weight);
    void shortestPath(int x);
    private:
    typedef pair<int, int> integerPair;
    
}

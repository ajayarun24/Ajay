

Ajay Arun

Sarthak Singh

Pranav Rajaraman

Jaylen Patel

**1. Leading Question**

With spring break coming up, many students/families are planning road-trips for some

bonding time with their loved ones! To help them out in this venture we aim to create a tool to

answer the following question: what is the most efficient route to get from point A to point B

**AND** see the pit-stop at the best sightseeing areas? A successful implementation of this tool will

output the shortest path between two inputted locations in the United States, and additionally

print the best tourist locations and their costs along this route!

**2. Dataset Acquisition and Processing**

We will use a dataset of the most popular tourist destinations in the United States and their

locations, we will download the data from

<https://www.touristmaker.com/blog/100-sights-in-usa/>, and convert the 100 places mentioned in

this article into an excel spreadsheet with the destination’s name, location(longitude and

latitude), and average cost of visiting of that city. We will get the average cost of living

<https://meric.mo.gov/data/cost-living-data-series>[ ](https://meric.mo.gov/data/cost-living-data-series)specifically the housing cost because that is

what travelers have to worry about. Once this data is into the excel spreadsheet we will convert it

into a csv file to make it easily parseable. We will parse this data against a map of the United

States, and given an input starting and stopping point, develop an algorithm to create the quickest

route with the best sight-seeing locations and the total cost of the trip. Some potential missing

entries could be a housing cost, but since we are the ones creating the dataset we can find our

data from multiple sources to fill the missing information. The most important information to

build our graph will be the distance which we can get for all data points using map software,

meaning there can be no errors on it.

**3. Graph Algorithms**

Our road trip planner algorithm will take in two graph data algorithms: it will firstly

construct a map of our desired region (the United States) by identifying which state will be





connected to the previous state with their edges based on their bordering state options (Prim’s

algorithm), secondly, it will find the shortest possible path from the start to end location using

Dijkstra’s algorithm (most efficient road-trip route). Since we will be using priority queues

(starting and ending points) in our Dijkstra’s algorithm implementation, the runtime will be

O(E + n(log(n)), where E is the amount of edges in a US map (google says average is 150-500

edges), so our runtime will be between O(150+n(log(n)) and O(500+n(log(n)). The runtime for

Prim’s algorithm is formulaically O(Elog(V)) where E is the number of edges (150-500) and V is

the number of vertices.

We will traverse these two graph data algorithms using a Depth-First Search (DFS), to

take in a starting point, ending point, and budget input, and output the most efficient (shortest)

route to get from point A to point B, which tourist locations will be visited along the way, and

how much over/under the proposed budget the trip will be. The DFS starts at the root node and

explores as far as possible along each branch before backtracking in left-right order The expected

runtime for our DFS search will be O(n) as in any DFS.

We will use Dijkstra’s Algorithm to find the shortest route, and we will use a DFS to

traverse that route. The dataset will be integrated with the route to output the recommended

road-trip “stops”/destinations along the journey to the end point.

**4. Timeline**

**Dates**

**Work**

**Deliverables**

Nov 8-15

Nov 16-22

Nov 23-29

Nov 30- Dec 6

Parsing data, creating edges

Writing BFS

Completed dataset

Traversal algorithm

Visualization of algorithms

Writing graph algorithms

Reviewing codebase, creating Presentation and completed

final presentation

codebase

Dec 7 - Dec 13

Creating written report, final

review

Completely finished project


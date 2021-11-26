Start 11/24 We met this week to check in on the progress of our past week, solve bugs, and develop plans for the next week. Additionally, we discussed the nd implementation of our program.


Last week update: 
We now have our dataset, makefile, and graph implementation ready. We decided that all of our data when parsed will be inside of a vector of a struct. This struct will contain information like name, state, neighboring states, etc. 


-----------------------------------------------------------------------


We decided on our IO for our program as the following: 
Input: 
- State(Ex. IL), State(EX. FL)
-   Means I want to go from Illinois to Florida
Output: 
- Total distance(Miles)
- Attraction Visited
- Some sort of cost metric
- PNG graph of path
- Did match budget
  - If it didn't “Consider visiting ___ fewer locations”
  - If it did this is within your budget
*This is our plan for now but could change as we start implementing it*


-----------------------------------------------------------------------

We then divided work for our next week: 

Get data into a struct for locations - Sarthak
We need to be able to compile multiple rows in two different CSV files into one vector. Parsing this data is integral to being able to make graphs and perform algorithms on the data we are using. 

-----------------------------------------------------------------------

Put data into graph structure - Pranav
Once we have put data into a vector we need to put it into a data structure that has nodes and edges and the implementation of that needs to be in a way that resembles a map

-----------------------------------------------------------------------

Dijkstra Algorithm - Ajay
To find the shortest path we are using Dijkstra's algorithm and that needs to be implemented after the graph is done being made. 

-----------------------------------------------------------------------

Find surrounding states from an input - Jaylen We need to begin figuring out how we will graphically implement our project so we need to understand how we can draw an arrow from one state to a surrounding one.  

----------------------------------------------------------------------- END: 11/28

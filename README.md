# Tourist road trip planner

This program helps create a road trip from one state to another with a variety of algorthms and traversals. Given an input and ending state this program will utilize a dataset of attractions in the United States to find the most efficient path while still hitting as many attractions as is possible. The algorithms used are Kruskals MST algorithm, BFS, and Dijstrikas algorithm. 

## The location of all major code, data, and results

1. Data folder
Inside of this folder are out two datasets: CS225 final project data.csv and data/neighbors-states.csv. The first contained the names, coordinates, index, and state of each attraction we are using. In the second was data relating to neighboring states in the US as we needed to know which edges our graph needed to have. 

1. Parsing.cpp and parsing.h
These files are how we parse csv data into a data strucutre that can be used to perform actions on. We parsed tge two csv's in the data folder

3. Roadtripgraph.cpp and Roadtripgraph.h
This is where all of the graph construction, algorthims, traversals, input/output, and visual output are done. To run the program, and instand of RoadTrupGraph needs to be made as it holds tourist attractions and creates objects which can run our algorithms. 

4. Calculator.cpp and calculator.h
Some of the earlier mentioned algorthms required us to perform some repeated math which these classes handled

5. us_map1.png
This is the file which updated after a program runs. This png will show the path that is depicted in terminal. 


## How to run the program

# To run the program you will need to run 
1. make
2. ./main

After this you will be prompted to enter some inputs to decide how you want to use our planner. Initially you will be asked for a starting state. A correct input requires you to use the two letter abberviation for each state. Illinois for example is IL. Then you will be asked for an ending state. After that, our program will run and gereate an MST, BFS traversal, and Djstrikas algorthm. 

You will then be asked to enter either "1" or anything else. This input will decide what we will be displaying on us_map1.png. 
1 means you want to show Djstrikas
Any other key means you want to show BFS

After this input, us_map1.png will be populated and the program is donw


## How to test the program 

# To test the program you need to run 
1. make test
2. ./test

# Our tests are broken down into a few sub sections

1. Parsing
We make sure that when we parse our data that our data structure(a vector) that that vector is not empty and contained the same number of items as the number of lines in our csv file. We also make sure that the same is done for our other csv(neihboring states)

3. Graph creation
We create an adjacency matrix and make sure that there are no edges between a node and itself

5. Djstrikas algorithm
We make sure that the total distance is less than that of bfs and the fact the traversal starts and ends in two different states
Ajay fill in

6. BFS
Pranav fill in

7. Kruskals algorithm
We make sure that the number of edges is equal to the number of nodes within our map


8. Output logic
We make sure that the hash of our input map is different from the output map as the output should have a traversal. 

# Tourist road trip planner

This program helps create a road trip from one state to another with a variety of algorthms and traversals. Given an input and ending state this program will utilize a dataset of attractions in the United States to find the most efficient path while still hitting as many attractions as is possible. The algorithms used are Kruskals MST algorithm, BFS, and Dijkstra's algorithm. 

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

To run the program you will need to run 
1. make
2. ./main

After this you will be prompted to enter some inputs to decide how you want to use our planner. Initially you will be asked for a starting state. A correct input requires you to use the two letter abberviation for each state. Illinois for example is IL. Then you will be asked for an ending state. After that, our program will run and gereate an MST, BFS traversal, and Dijkstra's algorthm. 

Here are the choices for states(Except Hawaii and Alaska):

<img width="720" alt="Screen Shot 2021-12-11 at 4 53 26 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/463b02af-b88e-4750-a2a2-ef4067418cde">


<img width="189" alt="Screen Shot 2021-12-11 at 4 49 14 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/6ce9bae2-c13c-4e04-a35a-90ccfbb84e2a">

<img width="549" alt="Screen Shot 2021-12-11 at 4 49 42 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/608b004e-b6e4-4afb-8807-4cc1621ddf47">


You will then be asked to enter either "1" or anything else. This input will decide what we will be displaying on us_map1.png. 
1 means you want to show Djstrikas. Any other key means you want to show BFS

<img width="564" alt="Screen Shot 2021-12-11 at 4 50 05 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/befbb406-7cae-48dc-99bf-273552234012">

After this input, us_map1.png will be populated and the program is done

![us_map1](https://media.github-dev.cs.illinois.edu/user/9991/files/731eee0a-3be9-4f78-ba52-8f2a47a2eb18)


## How to test the program 

# To test the program you need to run 
1. make test
2. ./test

###### Our tests are broken down into a few sub sections

1. Parsing
We make sure that when we parse our data that our data structure(a vector) that that vector is not empty and contained the same number of items as the number of lines in our csv file. We also make sure that the same is done for our other csv(neihboring states)

3. Graph creation
We create an adjacency matrix and make sure that there are no edges between a node and itself

5. Dijkstra's algorithm
We decided to use two test cases for Dijkstra's algorithm: in the first case, we test to ensure that the shortest path is actually generated, and in the second we test that the KM returned is accurate. For the shortest path test, we simply hand traced the distance between two input states (1 and 14, or Alabama and Arizona), and made sure the amount of stops which should be taken is equal to the size of the vector holding the states crossed. For the correct distance test, we again hand-traced the distance crossed and made sure it matched the distance returned (with a small tolerance).

6. BFS
Pranav fill in

7. Kruskals algorithm
We make sure that the number of edges is equal to the number of nodes within our map. This is the best way to make sure no node was included twice and that we in fact created a minimum spanning tree

8. Overall logic
We also included tests that compared BFS and Djstrikal algorithm to make sure they worked properly. We wanted to make sure the total distance traveled from a certain state to another had a shorter distance when running Djstrikas as compared to BFS

9. Output logic
We make sure that the hash of our input map is different from the output map as the output should have a traversal on it. Furthermore this test ensures that the image that we are using can be decoded by the PNG class

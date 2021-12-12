CS225 Final Project- Results
Final Deliverables:
In our proposal we sought out to be able to create a road-trip planner which could successfully find the quickest route from point A to point B using metrics for distance and cost. In our final implementation, we were able to do this, but were not able to implement the cost as well. Overall, in order to make our project successful, we implemented Kruskal’s Algorithm, DIjktra’s Algorithm, and Breadth First Search. Through writing each function, we made various observations, and the results were very similar to what we expected. In this project, the final deliverable is the program run in main. It takes a starting and ending state, and delivers the path given by BFS and Dijkstra’s, while also printing the Minimum Spanning Tree made by Kruskal’s. We also printed the shortest path onto a PNG as a part of the output. 

For each algorithm and the parsing function to put the data into C++, we wrote tests which checked whether the algorithms returned reasonable results, and whether the input data was parsed correctly in the first place. 

Although we found it a little difficult to write really specific tests because the graph was very dense, the tests we wrote did pass, and there will be pictures below.



<img width="768" alt="Screen Shot 2021-12-12 at 4 18 29 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/42a1bdb5-f78f-45ad-8ceb-a104e6740a74">

<img width="697" alt="Screen Shot 2021-12-12 at 4 18 49 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/a6ae7d43-fbf8-44c3-9674-c814394fc47d">



Besides writing test suites, the easy way to see the final result is to just run the main function. 

For the input to our algorithms we took in a state, and randomly picked one attraction in the state to start at and did the same for the end point. When ran from CA to NY the following output is returned:


<img width="574" alt="Screen Shot 2021-12-12 at 4 21 28 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/1769f2bc-c992-4b75-9b55-7c5b1ebb10d8">

The map output looks like this:

<img width="1158" alt="Screen Shot 2021-12-12 at 4 21 56 PM" src="https://media.github-dev.cs.illinois.edu/user/9991/files/1ab6d904-9248-41d9-9648-24065c5750ec">


Discoveries:
We ran into a few problems and made a few discoveries throughout the course of this project. But I think they can be condensed to just two things. First of all, when writing Dijkstra’s we ended up getting paths which were not efficient and sometimes even longer than BFS. However, we realized that we weren’t updating the weights of the vertices in the queue everytime they were added, which led to less efficient minimum routes. We also discovered that we needed to have an attraction in each state in order to find the most efficient path in the graph. When that condition was not met, we were met with errors, bad routes, and more. Overall, there were a few major issues we faced, but persevered to get a working result.

Final Thoughts:
We thought that the results were very interesting, and were surprised at the efficiency and ingenuity and some of the algorithms we were implementing. Although we faced some problems during the project, the results were pretty compelling. A nice addition would have been to add more factors like cost, time to travel, and more. Overall we accomplished everything we sought out to, but feel like we could have done even more interesting things with the data. 

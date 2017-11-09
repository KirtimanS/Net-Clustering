# Sparse-Net-Clustering
Partitioning large connected graphs into clusters.
Achieves 3 objectives:
1. Generates a spine in graphs, approximating the diameter. 
2. Finds clusterheads(Landmarks) in graphs.  
3. Assigns clusters nodes to Landmarks. 

# Getting Started
### Prerequisites
* GNU C++11 Compiler
* Linux OS (Mac OS and Windows would work as well with a little bit of tweaking)


### Installing

Linux systems nowadays ship with a native gcc c++11 complier. However, this is not installed by default. To do this a comprehensive guide may be found here: 
* Ubuntu - [Installing GNU C and GNU C++ Compilers](https://help.ubuntu.com/community/InstallingCompilers) - similar steps for other distributions
* Windows - [Visual Studio 2017 - C++ Desktop Workload](https://www.visualstudio.com/vs/community/) - other compliers may also be used 


### Theory:
We use an algorithm that takes a graph and clusters the vertices according to their nearness(number of hops) from a cluster center(Landmark). The way in which this is done is as follows:

1. Find the diameter of the graph and make the extremities Landmarks.
2. Look at the Central Node and make that a Landmark as well.
3. Look at the leaves of traversal tree form of the graph and majorize the leaves.
4. Choose the maximally distant leaf from the center after majorization and make it a Landmark and remove it from the list of eligible leaves.
5. Repeat from step 3 till an upper bound for cluster centers is reached.

### Authors:
* Kirtiman Sinha - 05/2017 - 08/2017

What's the input?
The input is an adjancency list, in the format as below:
```
vertex_id_1 vertex_id_2 vertex_id_3
```

where the above means vertex_id_1 is connected via edges to vertex_id_2 and vertex_id_3. The input has to be taken from stdin. Minor changes can be made to take inout from local machine.

What's the output?
Their are two outputs:
1. The first is a list of vertices with their associated landmarks or cluster centers(separated by a 0):
```
vertex_id_1 0 Landmark_1
```

2. The second output follows the first and is separated by a series of hyphens. This is the information needed to construct the Sparse  Net. This is provided as follows:
  1. The first line after vertex landmark assignment is the vertex_ids for the main Spine.
  2. The second and subsequent lines are the branches(going out of the main Spine) from the main Spine starting from the edges(leaves)        of those branches back towards the main Spine. The last vertex_id on that line is from the main Spine.
 An example is :
 ``` 
 ----------------
 vertex_1 vertex_2 vertex_3 vertex_4 vertex_5 vertex_6 
 vertex_7 vertex_8 vertex_4
 ```
 
 The first sequence of vertex_ids above is the main Spine and the second sequence is a sub-branch out of the main branch connected by ```vertex_4``` to the main branch.
  
  

Developed as a part of the Danish Project. Please drop an email to: kirtiman.sinha14@gmail.com in case of bugs/issues or questions. 

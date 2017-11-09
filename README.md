# Net-Clustering

Achieves 3 objectives:
1. Generates a spine in graphs, approximating the diameter. 
2. Finds clusterheads(Landmarks) in graphs.  
3. Assigns clusters nodes to Landmarks. 

Sparse Net Clustering:
We use an algorithm that takes a graph and clusters the vertices according to their nearness(number of hops) from a cluster center(Landmark). The way in which this is done is as follows:


What's the input?
The input is an adjancency list, in the format as below:
```
vertex_id_1 vertex_id_2 vertex_id_3
```

where the above means vertex_id_1 is connected via edges to vertex_id_2 and vertex_id_3. The input has to be taken from stdin. Minor changes can be made to take inout from local machine.

What's the output?
Their are two outputs:
1. The first is a list of vertices with their associated landmarks or cluster centers(separated by a 0):
vertex_id_1 0 Landmark_1

2. The second output is the information needed to construct the Sparse Net. This is provided as follows:
  1. The first line after vertex landmark assignment is the vertex_ids for the main Spine.
  2. The second and subsequent lines are the branches(going out of the main Spine) from the main Spine starting from the edges(leaves) of      those branches back towards the main Spine. The last vertex_id on that line is from the main Spine.
  

Developed as a part of the Danish Project.

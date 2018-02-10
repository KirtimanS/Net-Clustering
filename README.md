# Sparse-Net-Clustering
Partitioning large connected graphs into clusters.
Achieves 3 objectives:
1. Generates a spine in graphs, approximating the diameter. 
2. Finds clusterheads(Landmarks) in graphs.  
3. Assigns clusters nodes to Landmarks. 

### Quick Link(s): 
* [Package Usage and Algorithm](https://github.com/KirtimanS/Net-Clustering/wiki)  - the Why and Hows.

# Getting Started
### Prerequisites
* GNU C++11 Compiler
* Linux OS (Mac OS and Windows would work as well with a little bit of tweaking)


### Installing

Linux systems nowadays ship with a native gcc c++11 complier. However, this is not installed by default. To do this a comprehensive guide may be found here: 
* Ubuntu - [Installing GNU C and GNU C++ Compilers](https://help.ubuntu.com/community/InstallingCompilers) - similar steps for other distributions

For other OS:
* Windows - [Visual Studio 2017 - C++ Desktop Workload](https://www.visualstudio.com/vs/community/) - other compliers may also be used 
* OS X - [Installing C++ binaries on OS X](https://stackoverflow.com/questions/34340578/installing-c-libraries-on-os-x)

### Local Deployment:
* Ubuntu - All that's needed is compliling the binary using a g++11 compiler and running it after giving the input(as specified in the wiki) to stdin. 
* Windows - The binary may be compiled by command line arguments(if a c++ compiler is installed).

### Development:

Development of this binary has been done purely using C++. Since this is the engine on which the main framework for graph exploration is run, we wanted the code to be as optimized and efficient as possible and hence the use of C++ as opposed to Java or Python.

## Results:

The results look quite promising for an algorithm that tries to simulate k-means. For smaller graphs that are clearly separated the algorithm works spectacularly well. For more complex denser graphs, the clustering isn't as clean. This is done however, on purpose since for some requirements of the project dense hairballs of vertices needed to be broken up as symmetrically as possible.

![Alt text](https://github.com/KirtimanS/Net-Clustering/blob/master/1.1.png)



### Authors:
* Kirtiman Sinha - 05/2017 - 08/2017

### Acknowledgements:

* [PurpleBooth's comprehensive guide for this README](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)



Developed as a part of the Danish Project.  

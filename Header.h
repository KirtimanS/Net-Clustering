#ifndef NODECLASS_H
#define NODECLASS_H

#include <vector>
#include<set>
#include<map>


using namespace std;

class Node
{
public:
	int _id, degree, prev = 0, next = 0, landmark = NULL, spine = 0;
	vector <int> neighbors, dist_to_lmrk;
};

//function declarations - since there are many modules, using just one header file for all declarations
tuple <vector <Node>, map <int, int> > Pop_Graph(map <int, vector <int>>);
map <int, vector <int>> Pop_Map();
vector <Node> clean_dist_lmrk(vector <Node>);
tuple <vector <Node>, int, set <int>> BFS(vector <Node>, map <int, int>, int);
vector <int> Trace_Spine_Path(vector <Node>, map <int, int>, int, int);
tuple <vector <Node>, set <int>> find_leaves(vector <Node>, map <int, int>, vector <int>);
tuple <vector <Node>, map<int, int>> unrooted_tree(vector <Node>, map <int, int>, set <int>, vector <int>);
int Peel_1(vector <Node>, vector <int>, map <int, int>);
vector <int> Major_Filter(vector <int> leaves_id, vector <Node> Graph, map <int, int> id_index);
set <int> limit_k_hops(vector <int>, vector <Node>, map <int, int>, int);
tuple <vector <int>, vector <Node>> Clean_Up_Lmrks(vector <int>, vector <Node>, map <int, int>);
vector <Node> copy_dist_to_lmrk(vector <Node>, vector <Node>);
int farthest_lmrk(vector <int>, vector <Node> Graph, map <int, int>);
vector <int> lmrk_2_branch(vector <Node>, map <int, int>, int, vector<int>);
tuple <int, vector <int>> Add_New_Landmark(set <int>, vector <Node>, map <int, int>, set <int>);
vector <Node> Assign_Nodes(vector <int>, vector <Node>, map <int, int>);
void Display_Graph(vector <Node>, vector <int>, vector< vector <int>>);

#endif // NODECLASS_H


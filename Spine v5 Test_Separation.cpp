// Spine v5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Header.h"
#include <deque> 
#include <tuple>
#include <algorithm>
#include <iterator>

int main()
{
	int cen_node, spine_end_1, spine_end_2, diameter, dummy_int, lmrk_2, new_lmrk;
	vector <Node> Graph, Landmark_Node_vec, spine_vec, dummy_graph, net_graph_inter, net_graph;
	set <int> leaves, leaves_2, leaves_k_dist, dummy_set;
	vector <int> Landmark_id, spine_net_uo, leaves_vec, net_branch, spine, filt_leaves;
	map <int, int> id_index, net_id_index;
	multimap <int, int> leaves_distance;
	vector <vector <int>> net_o;

	typedef map<int, vector<int> > adjacency_template;
	adjacency_template adj_list;
	adj_list = Pop_Map();
	tie(Graph, id_index) = Pop_Graph(adj_list);

	tie(Graph, spine_end_1, dummy_set) = BFS(Graph, id_index, -2);

	tie(Graph, spine_end_2, dummy_set) = BFS(Graph, id_index, spine_end_1);

	Graph = clean_dist_lmrk(Graph);

	spine = Trace_Spine_Path(Graph, id_index, spine_end_2, spine_end_1);
	net_o.push_back(spine);
	set <int> net_uo_set(spine.begin(), spine.end());

	tie(net_graph_inter, leaves) = find_leaves(Graph, id_index, spine);

	tie(net_graph, net_id_index) = unrooted_tree(net_graph_inter, id_index, leaves, spine);

	copy(leaves.begin(), leaves.end(), back_inserter(leaves_vec));

	cen_node = Peel_1(net_graph, leaves_vec, net_id_index);
	Landmark_id.push_back(cen_node);
	leaves_vec.erase(remove(leaves_vec.begin(), leaves_vec.end(), cen_node), leaves_vec.end());
	tie(Graph, dummy_int, dummy_set) = BFS(Graph, id_index, cen_node);
	net_graph = copy_dist_to_lmrk(Graph, net_graph);

	lmrk_2 = farthest_lmrk(leaves_vec, net_graph, net_id_index);
	Landmark_id.push_back(lmrk_2);
	leaves_vec.erase(remove(leaves_vec.begin(), leaves_vec.end(), lmrk_2), leaves_vec.end());
	tie(Graph, dummy_int, dummy_set) = BFS(Graph, id_index, lmrk_2);
	net_graph = copy_dist_to_lmrk(Graph, net_graph);
	net_branch = lmrk_2_branch(net_graph, net_id_index, lmrk_2, spine);
	net_o.push_back(net_branch);
	for (int i = 0; i < net_branch.size(); i++)
	{
		net_uo_set.insert(net_branch[i]);
	}


	while (Landmark_id.size() < log2(Graph.size()) | leaves_vec.size() == Landmark_id.size())
	{
		filt_leaves = Major_Filter(leaves_vec, net_graph, net_id_index);

		leaves_k_dist = limit_k_hops(filt_leaves, net_graph, id_index, 3);

		if (leaves_k_dist.size() == 0)
		{
			break;
		}

		tie(new_lmrk, net_branch) = Add_New_Landmark(leaves_k_dist, net_graph, net_id_index, net_uo_set);
		Landmark_id.push_back(new_lmrk);
		net_o.push_back(net_branch);

		for (int i = 0; i < net_branch.size(); i++)
		{
			net_uo_set.insert(net_branch[i]);
		}

		leaves_vec.erase(remove(leaves_vec.begin(), leaves_vec.end(), new_lmrk), leaves_vec.end());
		tie(Graph, dummy_int, dummy_set) = BFS(Graph, id_index, new_lmrk);
		net_graph = copy_dist_to_lmrk(Graph, net_graph);
	}



	Graph = Assign_Nodes(Landmark_id, Graph, id_index);
	//leaves_distance = tree_BFS(spine, Graph, id_index, new_lmrk, leaves_vec);

	//leaves_no_major = Major_Remove(leaves_vec, Graph, id_index);



	//Graph = updat_dist_tolmrk(spine_path, Graph, id_index, spine_end_2, 1);

	/*while (log2(Graph.size()) > Landmark_id.size())
	{
	for (int i = 0; i < leaves_vec.size(); i++)
	{
	if (find(Landmark_id.begin(), Landmark_id.end(), leaves_vec[i]) != Landmark_id.end())
	{
	leaves_vec.erase(remove(leaves_vec.begin(), leaves_vec.end(), leaves_vec[i]), leaves_vec.end());
	}
	}

	copy(spine_path.begin(), spine_path.end(), inserter(spine_set, spine_set.end()));

	tie(new_lmrk, new_sub_spine) = Add_New_Landmark(leaves_vec, Graph, id_index, spine_set);

	if (new_lmrk == NULL)
	{
	break;
	}
	else
	{
	Landmark_id.push_back(new_lmrk);
	spine_path.push_back(0);
	spine_path.insert(spine_path.end(), new_sub_spine.begin(), new_sub_spine.end());
	}

	}




	if (diameter >= 6)
	{
	int new_lmrk_ind = diameter / 2;
	Landmark_id.push_back(spine_path[new_lmrk_ind]);

	}


	for (int i = 0; i < Landmark_id.size(); i++)
	{
	Landmark_Node_vec.push_back(Graph[id_index.find(Landmark_id[i])->second]);
	}



	Graph = Assign_Nodes(Landmark_Node_vec, Graph, id_index);*/

	tie(Landmark_id, Graph) = Clean_Up_Lmrks(Landmark_id, Graph, id_index);

	Display_Graph(Graph, Landmark_id, net_o);

	return 0;
}


/*tuple < set <int>, vector <Node>, vector <vector <int>>, vector <int> > Spine_Expansion(vector <int> net_path_uo, map <int, int> id_map, vector <Node> Graph)           //not needed as algorithmic logic changed
{
map <int, int> neighbor_map;
set <int> leaves;
vector <int> spine, leaves_vec;
vector <vector <int>> net_path_o;

spine = net_path_uo;
net_path_o.push_back(net_path_uo);


for (int i = 0; i < net_path_uo.size(); i++)
{
for (int j = 0; j < Graph[id_map.find(net_path_uo[i])->second].neighbors.size(); j++)
{
if (find(net_path_uo.begin(), net_path_uo.end(), Graph[id_map.find(net_path_uo[i])->second].neighbors[j]) != net_path_uo.end())
{

}
else
{
if (neighbor_map.count(Graph[id_map.find(net_path_uo[i])->second].neighbors[j]))
{
neighbor_map.find(Graph[id_map.find(net_path_uo[i])->second].neighbors[j])->second += 1;
}
else
{
neighbor_map.insert(make_pair(Graph[id_map.find(net_path_uo[i])->second].neighbors[j], 1));
Graph[id_map.find(Graph[id_map.find(net_path_uo[i])->second].neighbors[j])->second].prev = Graph[id_map.find(net_path_uo[i])->second]._id;
}
}

}
}

net_path_uo.push_back(-1);

do
{
int min_deg_net, vert_min;
min_deg_net = neighbor_map.begin()->second;
vert_min = neighbor_map.begin()->first;

map <int, int> ::iterator ptr;
for (ptr = neighbor_map.begin(); ptr != neighbor_map.end(); ptr++)
{
if (min_deg_net > ptr->second)
{
min_deg_net = ptr->second;
vert_min = ptr->first;
}
}

net_path_uo.push_back(vert_min);
neighbor_map.erase(vert_min);


int map_old_size = neighbor_map.size();

for (int i = 0; i < Graph[id_map.find(vert_min)->second].neighbors.size(); i++)
{
if (find(net_path_uo.begin(), net_path_uo.end(), Graph[id_map.find(vert_min)->second].neighbors[i]) != net_path_uo.end())
{

}
else
{
if (neighbor_map.count(Graph[id_map.find(vert_min)->second].neighbors[i]))
{
neighbor_map.find(Graph[id_map.find(vert_min)->second].neighbors[i])->second += 1;
}
else
{
neighbor_map.insert(make_pair(Graph[id_map.find(vert_min)->second].neighbors[i], 1));
Graph[id_map.find(Graph[id_map.find(vert_min)->second].neighbors[i])->second].prev = vert_min;
}
}
}

if (neighbor_map.size() == map_old_size)
{
leaves.insert(vert_min);
}

} while (!neighbor_map.empty());

copy(leaves.begin(), leaves.end(), back_inserter(leaves_vec));

for (int i = 0; i < leaves_vec.size(); ++i)
{
//net_path_o.push_back(-1);
int curr = leaves_vec[i];
vector <int> temp;
while (!(find(spine.begin(), spine.end(), Graph[id_map.find(curr)->second]._id) != spine.end()))
{
temp.push_back(curr);
curr = Graph[id_map.find(curr)->second].prev;
}
temp.push_back(curr);
net_path_o.push_back(temp);
}

return tuple < set <int>, vector <Node>, vector <vector <int>>, vector <int> >(leaves, Graph, net_path_o, net_path_uo);
}*/


/*vector <int> Major_Remove(vector <int> leaves_id, vector <Node> Graph, map <int, int> id_map)
{
set <int> majorised;
for (int i = 0; i < leaves_id.size(); i++)
{
for (int j = 0; j < leaves_id.size(); j++)
{
int count = 0;
for (int k = 0; k < Graph[id_map.find(leaves_id[i])->second].dist_to_lmrk.size(); k++)
{
if (Graph[id_map.find(leaves_id[i])->second].dist_to_lmrk[k] > Graph[id_map.find(leaves_id[j])->second].dist_to_lmrk[k])
{
count += 1;
}
}
if (count == Graph[id_map.find(leaves_id[i])->second].dist_to_lmrk.size())
{
leaves_id.erase(leaves_id.begin() + j);
majorised.insert(leaves_id[j]);
}
}
}

return (leaves_id);
}*/


/*tuple <vector <Node>, int> Add_New_Lmrk(vector <Node> leaves)
{
vector <int> distance_vec, iter_diff, test, iter_list;
for (int i = 0; i < leaves.size(); i++)
{


for (int j = 0; j < leaves[i].dist_to_lmrk.size() - 1; j++)
{
iter_diff.push_back(abs(leaves[i].dist_to_lmrk[j] - leaves[i].dist_to_lmrk[j + 1]));
}

int curr = iter_diff.size() - 1;
while (curr > 0)
{
test = iter_diff;
iter_diff.clear();
int curr = test.size() - 1;
for (int j = 0; j < curr; j++)
{
iter_diff.push_back(abs(test[j] - test[j + 1]));
}
}
iter_list.push_back(iter_diff[0]);
}

int min = iter_list[0], min_leaf_ind = 0;
for (int i = 0; i < iter_list.size(); i++)
{
if (iter_list[i] < min)
{
min = iter_list[i];
min_leaf_ind = i;
}
}

leaves.erase(leaves.begin() + min_leaf_ind);

return tuple <vector <Node>, int>(leaves, leaves[min_leaf_ind]._id);
}*/


/*int iter_diff(vector <int> leaves, map <int, int> id_ind, vector <Node> Graph)
{
vector <vector <int> > leaves_dist;
vector <int> iter_diff_dist;

for (int i = 0; i < leaves.size(); ++i)
{
leaves_dist.push_back(Graph[id_ind.find(leaves[i])->second].dist_to_lmrk);
}

vector <int> dist_differ, temp;
for (int idx = 0; idx < leaves_dist.size(); ++idx)
{
dist_differ = leaves_dist[idx];
int curr = leaves_dist[idx].size() - 1;

do {
temp.clear();
for (int j = 0; j < curr; ++j)
{
temp.push_back(abs(dist_differ[j] - dist_differ[j + 1]));
}
dist_differ.clear();
dist_differ = temp;
curr = temp.size() - 1;
} while (temp.size() != 1);

iter_diff_dist.push_back(temp[0]);
}

//int min = *min_element(dist_differ.begin(), dist_differ.end());
int min_index = min_element(iter_diff_dist.begin(), iter_diff_dist.end()) - iter_diff_dist.begin();

int new_lmrk = leaves[min_index];

return (new_lmrk);
}*/










/*deque <int> leaf_q;
for (int i = 0; i < leaves.size(); i++)
{
leaf_q.push_back(leaves[i]);
}

set< int> vertx_cov;
while (leaf_q.size() > 2)
{
if (find(leaf_q.begin(), leaf_q.end(), Graph[id_map.find(leaf_q.front())->second].prev) != leaf_q.end())
{

}
else if (!vertx_cov.count(Graph[id_map.find(leaf_q.front())->second].prev))
{
leaf_q.push_back(Graph[id_map.find(leaf_q.front())->second].prev);
vertx_cov.insert(Graph[id_map.find(leaf_q.front())->second].prev);
}
vertx_cov.insert(leaf_q.front());
leaf_q.pop_front();
}

if (Graph[id_map.find(leaf_q[0])->second].prev != leaf_q[1])
{
leaf_q.pop_front();
}

return (leaf_q.front());*/

/*set <int> curr_leaf_set, previous_leaf_set(leaves.begin(), leaves.end()), nodes_left;

for (int i = 0; i < Graph.size(); ++i)
{
nodes_left.insert(Graph[i]._id);
}

set <int> ::iterator it;
curr_leaf_set = previous_leaf_set;
while (curr_leaf_set.size() > 2)
{
curr_leaf_set.clear();
for (it = previous_leaf_set.begin(); it != previous_leaf_set.end(); it++)
{
if (Graph[id_map.find(*it)->second].prev == 0)
{
for (int i = 0; i< Graph[id_map.find(*it)->second].neighbors.size(); i++)
{
if (nodes_left.count(Graph[id_map.find(*it)->second].neighbors[i]))
{
curr_leaf_set.insert(*nodes_left.find(Graph[id_map.find(*it)->second].neighbors[i]));
}
}
}
else
{
curr_leaf_set.insert(Graph[id_map.find(*it)->second].prev);
}
}
previous_leaf_set.clear();
previous_leaf_set = curr_leaf_set;

set <int> ::iterator node_ptr;
for (node_ptr = previous_leaf_set.begin(); node_ptr != previous_leaf_set.end(); node_ptr++)
{
nodes_left.erase(*node_ptr);
}
}

return(2165197);*/



/*multimap <int, int> tree_BFS(vector <int> spine, vector <Node> Graph, map <int, int> id_map, int lmrk, vector <int> leaves)
{
int curr = lmrk, i = 0;
multimap <int, int> leaves_dist;

int dist = 0;
while (!(find(spine.begin(), spine.end(), curr) != spine.end()))
{
curr = Graph[id_map.find(curr)->second].prev;
dist += 1;
}
leaves_dist.insert(make_pair(curr, dist));

do
{
int dist = 0;
curr = leaves[i];
while (!(find(spine.begin(), spine.end(), curr) != spine.end()))
{
curr = Graph[id_map.find(curr)->second].prev;
dist += 1;
}
leaves_dist.insert(make_pair(curr, dist));

i += 1;
} while (i < leaves.size());

int lmrk_spine_con = leaves_dist.begin()->first;
int lmrk_spine_dist = leaves_dist.begin()->second;
int lmrk_con_ind = find(spine.begin(), spine.end(), lmrk_spine_con) - spine.begin();

leaves_dist.erase(leaves_dist.begin());

map <int, int>::iterator it;
int leaf_spine_dist = 0;
for (it = leaves_dist.begin(); it != leaves_dist.end(); ++it)
{
int leaf_ind = find(spine.begin(), spine.end(), it->first) - spine.begin();
it->second += (abs(lmrk_con_ind - leaf_ind) + lmrk_spine_dist);
}

return (leaves_dist);
}*/







/*vector <int> net_capture(vector <Node> Graph, vector <int> leaves, vector <int> Spine, map <int, int> id_map)
{
vector <int> net;
set <int> spine_set(Spine.begin(), Spine.end());

net = Spine;

for (int i = 0; i < leaves.size(); i++)
{
net.push_back(-1);
int curr = leaves[i];
net.push_back(curr);
while (!spine_set.count(curr))
{
net.push_back(Graph[id_map.find(curr)->second].prev);
curr = Graph[id_map.find(curr)->second].prev;
}
}

return (net);
}*/
















































/*void Add_New_Lmrk(vector <Node> Graph, map <int, int> id_map, set <int> net, set <int> leaves)
{
set <int> ::iterator leaf_it;
map <int, int> one_leaf_to_spine, all_to_spine;
int infinite = pow(2, 31) - 1;
for (leaf_it = leaves.begin(); leaf_it != leaves.end(); leaf_it++)
{
deque <int> node_q;
node_q.push_back(*leaf_it);

while (!node_q.empty())
{
int s = node_q.front();
node_q.pop_front();
for (int i = 0; i < Graph[id_map.find(s)->second].neighbors.size(); ++i)
{
if (!one_leaf_to_spine.count(Graph[id_map.find(s)->second].neighbors[i]))
{
one_leaf_to_spine.insert(make_pair(Graph[id_map.find(s)->second].neighbors[i], one_leaf_to_spine.find(id_map.find(s)->second)->second + 1));
node_q.push_back(Graph[id_map.find(s)->second].neighbors[i]);

if (net.count(Graph[id_map.find(s)->second].neighbors[i]))
{
all_to_spine.insert(make_pair(*leaf_it, one_leaf_to_spine.find(id_map.find(s)->second)->second + 1));
break;
}
}
}
}
}
}*/








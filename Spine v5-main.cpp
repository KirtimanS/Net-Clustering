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

	tie(Landmark_id, Graph) = Clean_Up_Lmrks(Landmark_id, Graph, id_index);

	Display_Graph(Graph, Landmark_id, net_o);

	return 0;
}

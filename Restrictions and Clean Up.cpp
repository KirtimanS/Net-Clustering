#include "Header.h"
#include <string>
#include<random>
#include<algorithm>


set <int> limit_k_hops(vector <int> elgbl_leaves_vec, vector <Node> Graph, map <int, int> id_map, int k)
{
	set <int> elgbl_leaves(elgbl_leaves_vec.begin(), elgbl_leaves_vec.end());
	set <int> del_leaf;
	set <int> ::iterator it;
	for (it = elgbl_leaves.begin(); it != elgbl_leaves.end(); ++it)
	{
		for (int i = 0; i < Graph[id_map.find(*it)->second].dist_to_lmrk.size(); i++)
		{
			if (Graph[id_map.find(*it)->second].dist_to_lmrk[i] < k)
			{
				del_leaf.insert(*it);
			}
		}
	}

	for (it = del_leaf.begin(); it != del_leaf.end(); ++it)
	{
		elgbl_leaves.erase(*it);
	}

	return (elgbl_leaves);
}


tuple <vector <int>, vector <Node>> Clean_Up_Lmrks(vector <int> lmrks, vector <Node> Graph, map <int, int> id_map)
{
	set <int> lmrk_set, del_lmrks_ind;
	vector <int> del_lmrks;
	vector <int> lmrk_lookup = lmrks;
	for (int i = 0; i < Graph.size(); ++i)
	{
		if (Graph[i].landmark != -1)
		{
			lmrk_set.insert(Graph[i].landmark);
		}
	}

	if (lmrk_set.size() != lmrks.size())
	{
		for (int i = 0; i < lmrks.size(); i++)
		{
			if (!lmrk_set.count(lmrks[i]))
			{
				del_lmrks.push_back(lmrks[i]);
				del_lmrks_ind.insert(i);
			}
		}
	}

	for (int i = 0; i < del_lmrks.size(); i++)
	{
		lmrks.erase(remove(lmrks.begin(), lmrks.end(), del_lmrks[i]), lmrks.end());
	}

	for (int i = 0; i < del_lmrks.size(); ++i)
	{
		int min = Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk[0];
		int min_index = 0;
		for (int j = 0; j < Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk.size(); ++j)
		{
			if (min > Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk[j] && !del_lmrks_ind.count(j))
			{
				min = Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk[j];
				min_index = j;
			}
		}

		vector <int> Equi_Lmrk;
		for (int k = 0; k < Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk.size(); ++k)
		{
			if (min == Graph[id_map.find(del_lmrks[i])->second].dist_to_lmrk[k] && !del_lmrks_ind.count(k))
			{
				Equi_Lmrk.push_back(k);
			}
		}

		if (Equi_Lmrk.size() > 1)
		{
			random_device seed;
			mt19937 engine(seed());
			uniform_int_distribution<int> choose(0, Equi_Lmrk.size() - 1);
			min_index = Equi_Lmrk[choose(engine)];
		}

		Graph[id_map.find(del_lmrks[i])->second].landmark = lmrk_lookup[min_index];
	}

	return tuple <vector <int>, vector <Node>>(lmrks, Graph);
}





vector <Node> copy_dist_to_lmrk(vector <Node> Graph, vector <Node> net_graph)
{
	for (int i = 0; i < net_graph.size(); ++i)
	{
		net_graph[i].dist_to_lmrk = Graph[i].dist_to_lmrk;
		net_graph[i].prev = Graph[i].prev;
	}

	return (net_graph);
}

#include "stdafx.h"

#include"Header.h"
#include<random>

int farthest_lmrk(vector <int> leaves, vector <Node> Graph, map <int, int> id_map)
{
	int max = 0, max_leaf = NULL;
	for (int i = 0; i < leaves.size(); ++i)
	{
		if (max < Graph[id_map.find(leaves[i])->second].dist_to_lmrk[0])
		{
			max = Graph[id_map.find(leaves[i])->second].dist_to_lmrk[0];
			max_leaf = Graph[id_map.find(leaves[i])->second]._id;
		}
	}
	return (max_leaf);
}

vector <int> lmrk_2_branch(vector <Node> Graph, map <int, int> id_map, int lmrk_2, vector<int> spine)
{
	vector<int> path_to_lmrk, spine_to_lmrk_length;
	vector <vector <int>> spine_to_lmrk;
	for (int i = 0; i < spine.size(); i++)
	{
		int curr = spine[i];
		path_to_lmrk.push_back(curr);
		while (curr != lmrk_2)
		{
			curr = Graph[id_map.find(curr)->second].prev;
			path_to_lmrk.push_back(curr);
		}
		spine_to_lmrk_length.push_back(path_to_lmrk.size());
		spine_to_lmrk.push_back(path_to_lmrk);
	}

	int min = 0, min_path_idx = 0;
	for (int i = 0; i < spine_to_lmrk_length.size(); i++)
	{
		if (min > spine_to_lmrk_length[i])
		{
			min = spine_to_lmrk_length[i];
			min_path_idx = i;
		}
	}

	vector<int> select_path_idx;
	for (int i = 0; i < spine_to_lmrk_length.size(); i++)
	{
		if (min == spine_to_lmrk_length[i])
		{
			select_path_idx.push_back(i);
		}
	}

	if (select_path_idx.size() > 1)
	{
		random_device seed;
		mt19937 engine(seed());
		uniform_int_distribution <int> choose(0, select_path_idx.size() - 1);
		min_path_idx = select_path_idx[choose(engine)];
	}

	return(spine_to_lmrk[min_path_idx]);
}

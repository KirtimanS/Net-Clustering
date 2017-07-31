#include "stdafx.h"

#include"Header.h"
#include<map>
#include<algorithm>
#include<string>
#include<iostream>


tuple <vector <Node>, map<int, int>> unrooted_tree(vector <Node> Graph, map <int, int> id_map, set <int> leaves, vector <int> net)
{
	set <int> ::iterator it;
	set <int> net_set(net.begin(), net.end());
	vector <Node> net_graph;
	map <int, vector <int>> net_adj;
	map <int, int> net_id_index;
	for (it = leaves.begin(); it != leaves.end(); ++it)
	{
		int curr = *it;
		while (!net_set.count(curr))
		{
			if (!net_adj.count(curr))
			{
				net_adj.insert(pair <int, vector <int>>(curr, { Graph[id_map.find(curr)->second].prev }));
			}
			if (!net_adj.count(Graph[id_map.find(curr)->second].prev))
			{
				net_adj.insert(pair <int, vector <int>>(Graph[id_map.find(curr)->second].prev, { curr }));
			}
			if (net_adj.count(curr) && !(find(net_adj.find(curr)->second.begin(), net_adj.find(curr)->second.end(), Graph[id_map.find(curr)->second].prev) != net_adj.find(curr)->second.end()))
			{
				net_adj.find(curr)->second.push_back(Graph[id_map.find(curr)->second].prev);
			}
			if (net_adj.count(Graph[id_map.find(curr)->second].prev) && !(find(net_adj.find(Graph[id_map.find(curr)->second].prev)->second.begin(), net_adj.find(Graph[id_map.find(curr)->second].prev)->second.end(), curr) != net_adj.find(Graph[id_map.find(curr)->second].prev)->second.end()))
			{
				net_adj.find(Graph[id_map.find(curr)->second].prev)->second.push_back(curr);
			}
			curr = Graph[id_map.find(curr)->second].prev;
		}
	}

	for (int i = 0; i < net.size() - 1; ++i)
	{
		if (net_adj.count(net[i]))
		{
			net_adj.find(net[i])->second.push_back(net[i + 1]);
		}
		if (!net_adj.count(net[i]))
		{
			net_adj.insert(pair <int, vector<int>>(net[i], { net[i + 1] }));
		}
		if (net_adj.count(net[i + 1]))
		{
			net_adj.find(net[i + 1])->second.push_back(net[i]);
		}
		if (!net_adj.count(net[i + 1]))
		{
			net_adj.insert(pair <int, vector<int>>(net[i + 1], { net[i] }));
		}
	}


	int count = 0;
	map <int, vector <int> > ::iterator map_it;
	for (map_it = net_adj.begin(); map_it != net_adj.end(); map_it++)
	{
		Node temp;
		temp._id = map_it->first;
		temp.neighbors = map_it->second;
		temp.degree = temp.neighbors.size();

		net_graph.push_back(temp);
		net_id_index.insert(make_pair(map_it->first, count));
		count += 1;
	}

	return tuple <vector <Node>, map <int, int>>(net_graph, net_id_index);
}


int Peel_1(vector <Node> Graph, vector <int> leaves, map <int, int> id_map)       //peel vertices if they are leaves - find central node
{
	vector <Node> peel_graph = Graph;
	vector <int> peel_leaves = leaves, temp;
	set <int> vertx_cov(leaves.begin(), leaves.end());
	int break_cndtn = 0;

	while (1)
	{
		for (int i = 0; i < peel_leaves.size(); ++i)
		{

			for (int j = 0; j < peel_graph[id_map.find(peel_leaves[i])->second].neighbors.size(); ++j)
			{
				if (!vertx_cov.count(peel_graph[id_map.find(peel_leaves[i])->second].neighbors[j]))
				{
					peel_graph[id_map.find(peel_graph[id_map.find(peel_leaves[i])->second].neighbors[j])->second].degree -= 1;
					if (peel_graph[id_map.find(peel_graph[id_map.find(peel_leaves[i])->second].neighbors[j])->second].degree == 1)
					{
						temp.push_back(peel_graph[id_map.find(peel_graph[id_map.find(peel_leaves[i])->second].neighbors[j])->second]._id);
						vertx_cov.insert(peel_graph[id_map.find(peel_graph[id_map.find(peel_leaves[i])->second].neighbors[j])->second]._id);
					}
				}
			}
		}
		peel_leaves.clear();
		peel_leaves = temp;

		if (break_cndtn | vertx_cov.size() == peel_graph.size())
		{
			break;
		}

		temp.clear();



		if (peel_graph.size() - vertx_cov.size() <= 2)
		{
			break_cndtn = 1;
		}
	}


	return (temp[0]);
}


vector <int> Major_Filter(vector <int> leaves_id, vector <Node> Graph, map <int, int> id_index)
{
	multimap <int, int> major_map;
	vector <vector<int>> leaves_dist;
	vector <int> del_leaves, leaves = leaves_id;

	for (int i = 0; i < leaves.size(); ++i)
	{
		leaves_dist.push_back(Graph[id_index.find(leaves[i])->second].dist_to_lmrk);
	}

	for (int i = 0; i < leaves_dist.size(); ++i)
	{
		for (int j = 0; j < leaves_dist.size(); ++j)
		{
			int isGreater = 0, isEqual = 0, major = 0;
			for (int k = 0; k < leaves_dist[i].size(); k++)
			{
				if (leaves_dist[i][k] > leaves_dist[j][k])
				{
					isGreater += 1;
					//major += 1;
				}
				if (leaves_dist[i][k] == leaves_dist[j][k])
				{
					isEqual = 1;
				}

			}
			if ((isGreater + isEqual) == leaves_dist[i].size() && !(find(del_leaves.begin(), del_leaves.end(), leaves[j]) != del_leaves.end()))
			{
				major_map.insert(make_pair(leaves[i], leaves[j]));
				del_leaves.push_back(leaves[j]);
			}
		}
	}

	for (int i = 0; i < del_leaves.size(); ++i)
	{
		leaves.erase(remove(leaves.begin(), leaves.end(), del_leaves[i]), leaves.end());
	}

	return (leaves);

}

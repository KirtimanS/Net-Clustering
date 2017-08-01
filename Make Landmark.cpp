#include "stdafx.h"

#include "Header.h"
#include<deque>
#include<iterator>
#include<algorithm>
#include <functional>
#include<random>

vector <Node> clean_dist_lmrk(vector <Node> Graph)
{
	for (int i = 0; i < Graph.size(); ++i)
	{
		Graph[i].dist_to_lmrk.clear();
	}
	return (Graph);
}

tuple <int, vector <int>> Add_New_Landmark(set <int> leaf_set, vector <Node> lmrk_graph, map <int, int> lmrk_id_index, set <int> net)
{
	vector <int> leaves(leaf_set.begin(), leaf_set.end()), dummy;
	vector <Node> lmrk_graph_dupli = lmrk_graph;
	int infinite = (pow(2, 31) - 1), foundSpine = 0, distance_to_spine;
	deque <Node> bfs_queue;
	vector <int> leaves_dist, spine_subpath;
	vector < vector <int>> paths_to_spine;
	map <int, int> distance_map;

	for (int i = 0; i < leaves.size(); i++)
	{
		for (int j = 0; j < lmrk_graph.size(); j++)
		{
			if (lmrk_graph[j]._id == leaves[i])
			{
				distance_map.insert(make_pair(leaves[i], 0));
			}
			else
			{
				distance_map.insert(make_pair(lmrk_graph[j]._id, infinite));
			}
		}

		Node s = lmrk_graph[lmrk_id_index.find(leaves[i])->second];
		bfs_queue.push_back(s);
		while (!bfs_queue.empty())
		{
			Node u = bfs_queue.front();
			bfs_queue.pop_front();
			for (int k = 0; k < u.neighbors.size(); k++)
			{
				if (distance_map.find(u.neighbors[k])->second == infinite)
				{
					bfs_queue.push_back(lmrk_graph[lmrk_id_index.find(u.neighbors[k])->second]);
					distance_map.find(u.neighbors[k])->second = distance_map.find(u._id)->second + 1;

					lmrk_graph[lmrk_id_index.find(u.neighbors[k])->second].prev = u._id;
				}

				if (net.count(u.neighbors[k]))
				{
					foundSpine = 1;
					distance_to_spine = distance_map.find(u.neighbors[k])->second;

					int curr = lmrk_graph[lmrk_id_index.find(u.neighbors[k])->second]._id;

					while (curr != leaves[i])
					{
						spine_subpath.push_back(curr);
						curr = lmrk_graph[lmrk_id_index.find(curr)->second].prev;
					}
					spine_subpath.push_back(curr);

					break;
				}
			}
			if (foundSpine)
			{
				leaves_dist.push_back(distance_to_spine);
				break;
			}
		}

		paths_to_spine.push_back(spine_subpath);

		spine_subpath.clear();

		distance_map.clear();
		bfs_queue.clear();
		foundSpine = 0;
	}


	int max_dist_ind = distance(begin(leaves_dist), max_element(leaves_dist.begin(), leaves_dist.end()));


	auto equidistant = false;
	auto assign_conflict = false;

	if (adjacent_find(leaves_dist.begin(), leaves_dist.end(), not_equal_to<int>()) == leaves_dist.end())
	{
		auto equidistant = true;
	}
	else if (leaves_dist[max_dist_ind] <= 2)
	{
		auto assign_conflict = true;
	}

	if (equidistant && assign_conflict)
	{
		return tuple <int, vector <int>>(NULL, dummy);
	}

	else
	{
		return tuple<int, vector <int>>(leaves[max_dist_ind], paths_to_spine[max_dist_ind]);
	}
}


vector <Node> Assign_Nodes(vector <int> Landmark_id, vector <Node> ass_graph, map <int, int> id_index)
{
	int dummy;
	set <int> vertex_assigned, dummy2, Landmarks_set(Landmark_id.begin(), Landmark_id.end());
	vector <Node> Landmarks;

	for (int i = 0; i < ass_graph.size(); i++)
	{
		ass_graph[i].dist_to_lmrk.clear();
	}

	for (int i = 0; i < Landmark_id.size(); i++)
	{
		Landmarks.push_back(ass_graph[id_index.find(Landmark_id[i])->second]);
		tie(ass_graph, dummy, dummy2) = BFS(ass_graph, id_index, Landmark_id[i]);
	}

	int min, Landmark_tobeAss;
	for (int i = 0; i < ass_graph.size(); i++)
	{
		if (Landmarks_set.count(ass_graph[i]._id))
		{
			ass_graph[i].landmark = -1;
		}
		else if (ass_graph[i].landmark == NULL)
		{
			min = *min_element(ass_graph[i].dist_to_lmrk.begin(), ass_graph[i].dist_to_lmrk.end());
			Landmark_tobeAss = distance(ass_graph[i].dist_to_lmrk.begin(), min_element(ass_graph[i].dist_to_lmrk.begin(), ass_graph[i].dist_to_lmrk.end()));
			vertex_assigned.insert(ass_graph[i]._id);
		}

		if (ass_graph[i].landmark != -1)
		{
			vector <int> Equi_Lmrk_ass;
			for (int j = 0; j < ass_graph[i].dist_to_lmrk.size(); ++j)
			{
				if (min == ass_graph[i].dist_to_lmrk[j])
				{
					Equi_Lmrk_ass.push_back(j);
				}
			}

			if (Equi_Lmrk_ass.size() > 1)
			{
				random_device seed;
				mt19937 engine(seed());
				uniform_int_distribution <int> choose(0, Equi_Lmrk_ass.size() - 1);
				Landmark_tobeAss = Equi_Lmrk_ass[choose(engine)];
			}
			ass_graph[i].landmark = Landmarks[Landmark_tobeAss]._id;
		}
	}
	return(ass_graph);
}

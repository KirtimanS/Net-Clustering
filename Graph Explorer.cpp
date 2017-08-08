#include "Header.h"
#include<tuple>
#include<vector>
#include<map>
#include<deque>


tuple <vector <Node>, int, set <int>> BFS(vector <Node> bfs_graph, map <int, int> bfs_id_map, int chosen_vertx)
{
	map <int, int> distance, level_map;
	int chosen_ind, level = 0, leaf = 1, isRandom;
	set <int> leaves;

	if (chosen_vertx == -2)
	{
		chosen_ind = rand() % bfs_graph.size();
		isRandom = 1;
	}
	else
	{
		chosen_ind = bfs_id_map.find(chosen_vertx)->second;
		isRandom = 0;
	}


	int infinite = 2 ^ 31 - 1;
	Node s = bfs_graph[chosen_ind];


	for (int i = 0; i < bfs_graph.size(); i++)
	{
		if (i == chosen_ind)
		{
			distance.insert(make_pair(bfs_graph[i]._id, 0));
		}
		else
		{
			distance.insert(make_pair(bfs_graph[i]._id, infinite));
		}
	}

	deque <Node> bfs_queue;
	bfs_queue.push_back(s);
	level_map.insert(make_pair(s._id, level));
	while (!bfs_queue.empty())
	{
		level += 1;
		leaf = 1;
		Node u = bfs_queue.front();
		bfs_queue.pop_front();
		for (int i = 0; i < u.neighbors.size(); i++)
		{
			if (distance.find(u.neighbors[i])->second == infinite)
			{
				int neighbor_ind = bfs_id_map.find(u.neighbors[i])->second;
				bfs_queue.push_back(bfs_graph[neighbor_ind]);

				distance.find(u.neighbors[i])->second = distance.find(u._id)->second + 1;

				bfs_graph[neighbor_ind].prev = u._id;

				level_map.insert(make_pair(bfs_graph[neighbor_ind]._id, level));

				leaf = 0;
			}
		}

		if (leaf == 1)
		{
			leaves.insert(u._id);
		}
	}

	int max_val = 0, max_vert;
	max_val = distance.begin()->second;

	map <int, int>::iterator max_ptr;
	for (max_ptr = distance.begin(); max_ptr != distance.end(); max_ptr++)
	{
		if (max_val <= max_ptr->second)                                //farthest point estimate from distance after BFS
		{
			max_val = max_ptr->second;
			max_vert = max_ptr->first;
		}

		if (isRandom == 0)                                              // adding landmark distances
		{
			int index = bfs_id_map.find(max_ptr->first)->second;
			bfs_graph[index].dist_to_lmrk.push_back(max_ptr->second);
		}
	}

	/*map <int, int>::iterator ptr;											// Check if BFS good?
	for (ptr = distance.begin(); ptr != distance.end(); ptr++)
	{
	cout << "\nVertex " << ptr->first << ": ";
	cout << "Distance :" << ptr->second;
	}*/

	return tuple <vector <Node>, int, set <int>>(bfs_graph, max_vert, leaves);
}


vector <int> Trace_Spine_Path(vector <Node> trace_graph, map <int, int> graph_id, int start_id, int stop_id)
{
	int curr = start_id;
	int curr_ind = graph_id.find(curr)->second;
	trace_graph[curr_ind].spine = 1;
	vector <int> path;
	while (curr != stop_id)
	{
		path.push_back(curr);
		curr = trace_graph[curr_ind].prev;
		curr_ind = graph_id.find(curr)->second;
		trace_graph[curr_ind].spine = 1;
	}
	path.push_back(curr);

	/*cout << "Path : ";
	for (int i = 0; i < path.size(); i++)
	{											//check if correct path traced.
	cout << path[i] << "  ";
	}*/

	return (path);
}


tuple <vector <Node>, set <int>> find_leaves(vector <Node> Graph, map <int, int> id_index, vector <int> spine)
{
	set <int> vertx_covrd, leaves, spine_set(spine.begin(), spine.end());
	deque <int> node_queue(spine.begin(), spine.end());

	while (!node_queue.empty())
	{
		int s = node_queue.front();
		node_queue.pop_front();
		int isLeaf = 1;
		for (int i = 0; i < Graph[id_index.find(s)->second].neighbors.size(); ++i)
		{
			if (!vertx_covrd.count(Graph[id_index.find(s)->second].neighbors[i]))
			{
				vertx_covrd.insert(Graph[id_index.find(s)->second].neighbors[i]);
				Graph[id_index.find(Graph[id_index.find(s)->second].neighbors[i])->second].prev = Graph[id_index.find(s)->second]._id;
				if (!spine_set.count(Graph[id_index.find(s)->second].neighbors[i]))
				{
					node_queue.push_back(Graph[id_index.find(s)->second].neighbors[i]);
				}
				isLeaf = 0;
			}
		}

		if (isLeaf == 1)
		{
			leaves.insert(s);
		}
	}

	if (Graph[id_index.find(spine[0])->second].degree == 1)
	{
		leaves.insert(spine[0]);
	}

	return tuple< vector <Node>, set<int> >(Graph, leaves);
}

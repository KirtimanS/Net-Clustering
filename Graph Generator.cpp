#include "Header.h"
#include<tuple>
#include<iostream>
#include <fstream>
#include <sstream>


tuple <vector <Node>, map <int, int> > Pop_Graph(map <int, vector <int>> adj)
{
	int id_ptr = 0;
	map <int, int> id_map;
	map<int, vector <int>> ::iterator ptr;
	vector <Node> graph;

	for (ptr = adj.begin(); ptr != adj.end(); ptr++)
	{
		Node temp;
		temp._id = ptr->first;
		temp.degree = ptr->second.size();
		for (int i = 0; i < ptr->second.size(); i++)
		{
			temp.neighbors.push_back(ptr->second[i]);
		}

		graph.push_back(temp);
		id_map.insert(make_pair(temp._id, id_ptr));
		id_ptr += 1;
	}

	return tuple <vector <Node>, map <int, int>>(graph, id_map);
}



map <int, vector <int>> Pop_Map()
{
	typedef map<int, vector<int> > AdjacencyList;
	string line;
	AdjacencyList al;

	while (getline(cin, line)) 
	{
		istringstream buffer(line);

		int num;
		buffer >> num;

		auto it = al.insert(make_pair(num, AdjacencyList::mapped_type())).first;
		
		while (!buffer.eof()) 
		{
		    buffer >> num;
		    it->second.push_back(num);
        	}
    }
	return (al);
}

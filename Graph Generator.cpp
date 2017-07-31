#include "stdafx.h"

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
	ifstream file("C:\\New folder\\test_graphs\\test_graphs\\test_this_one.txt");

	string line;

	AdjacencyList al;
	while (!file.eof())
	{
		getline(file, line);

		istringstream buffer(line);
		int num;
		buffer >> num;
		//cout << line <<endl;
		auto it = al.insert(std::make_pair(num, AdjacencyList::mapped_type())).first;
		while (!buffer.eof())
		{
			buffer >> num;
			it->second.push_back(num);
		}
	}

	/*AdjacencyList::iterator ptr;      //-> check map if good input?
	for (ptr = al.begin(); ptr != al.end(); ptr++)
	{
	cout << "\nVertex "<<ptr->first<<": ";
	for (int i = 0; i < ptr->second.size(); i++)
	{
	cout << ptr->second[i] << "   ";
	}
	}*/
	return (al);
}
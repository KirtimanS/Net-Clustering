#include"Header.h"
#include<iostream>

void Display_Graph(vector <Node> Graph, vector <int> Landmarks, vector< vector <int>> net) 
	for (int i = 0; i < Graph.size(); i++)
	{
		cout << Graph[i]._id << " 0 " << Graph[i].landmark << endl;
	}
	cout << "---" << endl;
	for (int i = 0; i < net.size(); i++)
	{
		for (int j = 0; j < net[i].size(); j++)
		{
			cout << net[i][j] << " ";
		}
		cout << "\n";
	}
}

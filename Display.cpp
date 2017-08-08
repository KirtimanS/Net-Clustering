#include"Header.h"
#include<iostream>

void Display_Graph(vector <Node> Graph, vector <int> Landmarks, vector< vector <int>> net) //needed by the vis.js
{
	/*cout << "Landmarks: ";                                       //check if Landmarks ahve been evaluated properly.
	for (int i = 0; i < Landmarks.size(); i++)
	{
	cout <<"  "<<Landmarks[i];
	}
	cout << "\n";*/

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



/*void Display_Graph(vector <Node> Graph, vector <int> Landmarks, vector< vector <int>> net)      // for self - display all
{
map <int, int> Disp_Map_sizes;
map <int, vector<int>> Disp_Map_sets;
cout << "Landmarks :";
for (int i = 0; i < Landmarks.size(); i++)
{
cout << Landmarks[i] << "  ";
}

cout << "\n\n";

for (int i = 0; i < Graph.size(); i++)
{
cout << "\n" << Graph[i]._id << "   " << Graph[i].landmark;
}

cout << "\n\nNet : ";
for (int i = 0; i < net.size(); i++)
{
cout << "\n";
for (int j = 0; j < net[i].size(); j++)
{
cout << net[i][j] << "  ";
}
}

cout << "\n\n";
/*for (int i = 0; i < Graph.size(); i++)
{
cout << "Vertex Id : " << Graph[i]._id << "  Back Pointer :" << Graph[i].prev << "  Nearest Landmarks :" << Graph[i].landmark << endl;
}

for (int i = 0; i < Graph.size(); i++)
{
if (Graph[i].landmark != -1)
{
if (Disp_Map_sizes.find(Graph[i].landmark) == Disp_Map_sizes.end())
{
Disp_Map_sizes.insert(make_pair(Graph[i].landmark, 1));
Disp_Map_sets.insert(pair <int, vector <int> >(Graph[i].landmark, { Graph[i]._id }));
}
else
{
Disp_Map_sizes.find(Graph[i].landmark)->second += 1;
Disp_Map_sets.find(Graph[i].landmark)->second.push_back(Graph[i]._id);
}
}
}

/*cout << "Landmark Sizes :-" << endl;
map<int, int> ::iterator it;
for (it = Disp_Map_sizes.begin(); it != Disp_Map_sizes.end(); ++it)
{
cout << "\nLandmark: " << it->first << "  " << it->second;
}

cout << "\n\nLandmark Sets :-";
map <int, vector <int>>::iterator ptr;
for (ptr = Disp_Map_sets.begin(); ptr != Disp_Map_sets.end(); ++ptr)
{
cout << "\n\nLandmark: " << ptr->first <<" ->  ";
for (int j = 0; j < ptr->second.size(); ++j)
{
cout << ptr->second[j] << "  ";
}
}
}*/

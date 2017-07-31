#pragma once
#ifndef MAKE_LMRK_H
#define MAKE_LMRK_H

#include <tuple>
#include "Header.h"


tuple <int, vector <int>> Add_New_Landmark(set <int> leaf_set, vector <Node> lmrk_graph, map <int, int> lmrk_id_index, set <int> net);
vector <Node> Assign_Nodes(vector <int> Landmark_id, vector <Node> ass_graph, map <int, int> id_index);
vector <Node> clean_dist_lmrk(vector <Node> Graph);

#endif // !MAKE_LMRK_H
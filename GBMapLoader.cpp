#include <fstream>
#include <iostream>
#include "GBMapLoader.h"
using namespace std;


GBMapLoader::GBMapLoader() {};

void GBMapLoader::loadMap(string filename) {
	vector<vector<Node*>> temp_map = vector<vector<Node*>>();
	ifstream input(filename);
	string delim = ",";

	/*
	INITIALIZE MAP WITH EMPTY NODES
	*/
	int y = 0;
	for (string line; getline(input, line); )
	{
		// new row
		temp_map.push_back(vector<Node*>());

		// split on commas, each token represents either a Node (N) or NULL (X)
		size_t i = 0;
		int x = 0;
		string token;

		// append delim to the line, to get last token of each row when splitting
		line = line + delim;

		while ((i = line.find(delim)) != string::npos) {
			token = line.substr(0, i);
			// create a new valid node if token is N
			if (token == "N")
				temp_map.back().push_back(new Node(x, y));
			// assign invalid node if token is X
			else if (token == "X")
				temp_map.back().push_back(new Node(x,y,false));

			line.erase(0, i + 1);
			x++;
		}
		y++;
	}
	
	// temp map is in inverse order. We now must correct this:
	this->map = vector<vector<Node*>>((temp_map[0].size()), vector<Node*>(temp_map.size()));
	for (size_t x = 0; x < temp_map.size(); x++)
		for (size_t y = 0; y < temp_map[x].size(); y++) 
			map[y][x] = temp_map[x][y];
	
	/*
	CONNECT NODES (INITIALIZE ADJACENCY LIST)
	*/
	for (size_t y = 0; y < map[0].size(); y++)
		for (size_t x = 0; x < map.size(); x++)
			if (*map[x][y]->valid) {
				if (y != 0)
					map[x][y]->edge_list[0] = map[x][y - 1]; // North
				else
					map[x][y]->edge_list[0] = new Node(x, y - 1, false); // give dummy invalid node

				if (x != map.size() - 1)
					map[x][y]->edge_list[1] = map[x + 1][y]; // East
				else
					map[x][y]->edge_list[1] = new Node(x + 1, y, false);

				if (y != map[x].size() - 1)
					map[x][y]->edge_list[2] = map[x][y + 1]; // South
				else
					map[x][y]->edge_list[2] = new Node(x, y + 1, false);

				if (x != 0)
					map[x][y]->edge_list[3] = map[x - 1][y]; // West
				else
					map[x][y]->edge_list[3] = new Node(x - 1, y, false);
			}


}

vector<vector<Node*>> GBMapLoader::getMap() {
	return this->map;
}


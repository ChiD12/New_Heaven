#include <vector>
#include <fstream>
#include <iostream>
#include "GBMapLoader.h"
using namespace std;

GBMapLoader::GBMapLoader() {};

void GBMapLoader::loadMap(string filename) {
	this->map = vector<vector<Node*>>();
	ifstream input(filename);
	string delim = ",";

	/*
	INITIALIZE MAP WITH EMPTY NODES
	*/
	int x = 0;
	for (string line; getline(input, line); )
	{
		// new row
		map.push_back(vector<Node*>());

		// split on commas, each token represents either a Node (N) or NULL (X)
		size_t i = 0;
		int y = 0;
		string token;

		// append delim to the line, to get last token of each row when splitting
		line = line + delim;

		while ((i = line.find(delim)) != string::npos) {
			token = line.substr(0, i);
			// create a new node if token is N
			if (token == "N")
				map.back().push_back(new Node(x, y));
			// assign NULL if token is X
			else if (token == "X")
				map.back().push_back(NULL);

			line.erase(0, i + 1);
			y++;
		}

		x++;
	}
	
	/*
	CONNECT NODES (INITIALIZE ADJACENCY LIST)
	*/
	
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++) {
			if(y != 0)
				map[x][y]->edge_list[0] = map[x][y - 1]; // North
			if(x != map.size()-1)
				map[x][y]->edge_list[1] = map[x + 1][y]; // East
			if(y != map[x].size()-1)
				map[x][y]->edge_list[2] = map[x][y + 1]; // South
			if(x != 0)
				map[x][y]->edge_list[3] = map[x - 1][y]; // West
		}
	}
}

vector<vector<Node*>> GBMapLoader::getMap() {
	return this->map;
}


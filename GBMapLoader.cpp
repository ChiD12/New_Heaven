#include <fstream>
#include <iostream>
#include "GBMapLoader.h"
using namespace std;


GBMapLoader::GBMapLoader() {};
GBMapLoader::~GBMapLoader() {
	map->clear();
	delete map;
	map = NULL;
}

void GBMapLoader::loadMap(int numPlayers) {
	vector<vector<Node*>> temp_map = vector<vector<Node*>>();
	string filename;
	switch (numPlayers) {
	case 2:
		filename = "twoPlayer.txt";
		break;
	case 3:
		filename = "threePlayer.txt";
		break;
	case 4:
		filename = "fourPlayer.txt";
		break;
	default:
		throw "Invalid number of players.";
	}
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

		// split on commas, each token represents either a Node (N) or Invalid Node (X)
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
				temp_map.back().push_back(new Node(x, y, false));
			else
				throw "ERROR LOADING GAME BOARD MAP: UNRECOGNIZABLE SYMBOL.";
			

			line.erase(0, i + 1);
			x++;
		}
		y++;
	}

	// temp map is in inverse order. We now must correct this:
	this->map = new vector<vector<Node*>>((temp_map[0].size()), vector<Node*>(temp_map.size()));
	for (size_t x = 0; x < temp_map.size(); x++)
		for (size_t y = 0; y < temp_map[x].size(); y++)
			map->at(y)[x] = temp_map[x][y];

	/*
	CONNECT NODES (INITIALIZE ADJACENCY LIST)
	*/
	for (size_t y = 0; y < map->at(0).size(); y++)
		for (size_t x = 0; x < map->size(); x++)
			if (*map->at(x)[y]->valid) {
				if (y != 0)
					map->at(x)[y]->edge_list->at(0) = map->at(x)[y - 1]; // North
				else
					map->at(x)[y]->edge_list->at(0) = new Node(x, y - 1, false); // give dummy invalid node

				if (x != map->size() - 1)
					map->at(x)[y]->edge_list->at(1) = map->at(x + 1)[y]; // East
				else
					map->at(x)[y]->edge_list->at(1) = new Node(x + 1, y, false);

				if (y != map->at(x).size() - 1)
					map->at(x)[y]->edge_list->at(2) = map->at(x)[y + 1]; // South
				else
					map->at(x)[y]->edge_list->at(2) = new Node(x, y + 1, false);

				if (x != 0)
					map->at(x)[y]->edge_list->at(3) = map->at(x - 1)[y]; // West
				else
					map->at(x)[y]->edge_list->at(3) = new Node(x - 1, y, false);
			}
}

vector<vector<Node*>>& GBMapLoader::getMap() {
	return *this->map;
}

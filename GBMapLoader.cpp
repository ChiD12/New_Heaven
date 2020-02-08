#include <vector>
#include <fstream>
#include <iostream>
#include "GBMapLoader.h"
using namespace std;

GBMapLoader::GBMapLoader() {};

void GBMapLoader::loadMap(string filename) {
	vector<vector<Node*>> map = vector<vector<Node*>>();
	ifstream input(filename);
	string delim = ",";

	int y = 0;
	for (string line; getline(input, line); )
	{
		// new row
		map.push_back(vector<Node*>());

		// split on commas, each token represents either a Node (N) or NULL (X)
		size_t i = 0;
		int x = 0;
		string token;
	
		// append delim to the line, to get last token of each row when splitting
		line = line + delim;

		while ((i = line.find(delim)) != string::npos) {
			token = line.substr(0, i);
			// create a new node if token is N
			if (token == "N")
				map.back().push_back(new Node(new int(x),new int(y)));
			// assign NULL if token is X
			else if (token == "X")
				map.back().push_back(NULL);
			
			line.erase(0, i + 1);
			x++;
		}

		y++;
	}

	this->gb = new GameBoard(map);
}

GameBoard* GBMapLoader::getGameBoard() {
	return this->gb;
}


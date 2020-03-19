#pragma once
#include <vector>
#include "Resources.h"
#include "Resources.h"
#include "GBMapLoader.h"

class GBMap {
public:
	vector<vector<Node*>>* pgbA;

	void update_edge_all();

	bool PlaceTile(HarvestTile* given_tile, int tlX, int tlY);
	vector<int> CalculateResources(int x, int y);
	void PrintResources(); //TODO Print to the players the current available resources reflected in the resource markers on the game board.

	GBMap();
	GBMap(int numPlayers);
	~GBMap();

	void PrintBoard();

};


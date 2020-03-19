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

	GBMap();
	GBMap(int numPlayers);
	~GBMap();

	void PrintBoard();

};


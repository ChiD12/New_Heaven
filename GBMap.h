#pragma once
#include <vector>
#include "Resources.h"
#include "Resources.h"
#include "GBMapLoader.h"

class GBMap {
public:

	vector<vector<Node*>>* pgbA;

	int* RMWood;
	int* RMStone;
	int* RMSheep;
	int* RMGrain;
	vector<BuildingTile*> *buildings;

	void update_edge_all();

	bool PlaceTile(HarvestTile* given_tile, int tlX, int tlY);
	vector<int> CalculateResources(int x, int y);

	GBMap();
	GBMap(int numPlayers);
	~GBMap();

	void PrintBoard();
	void PrintResources();
	void printVillageTiles();
};

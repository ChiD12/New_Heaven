#include <string>
#include "Resources.h"
#pragma once

using namespace std;

class GBMapLoader {
private:
	// GameBoard* gb;
	vector<vector<Node*>> map;

public:
	GBMapLoader();
	~GBMapLoader();

	vector<vector<Node*>> getMap();

	void loadMap(string filename);
};
#pragma once
#include "Resources.h"
#include "VGMapLoader.h"
#include <vector>

class VGMap {
    int* width;
    int* height;
    int* score;

	string* village_name; //Added by Nathan

    bool* forest_placed;
    bool* wheatfield__placed;
    bool* meadow_placed;
    bool* quarry_placed;

public:
    VGMap();
    ~VGMap();
    bool placeTile(int, int, bool, BuildingTile);
	void setName(string given_name);
    int calculateScore();
    void PrintVillageBoard();
    std::vector<vector<BuildingTile*>> *map;

};
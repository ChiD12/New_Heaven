#pragma once
#include "Resources.h"
#include "VGMapLoader.h"
#include <vector>

class VGMap {
    int* score;

	string* village_name; //Added by Nathan

    bool* forest_placed;
    bool* wheatfield__placed;
    bool* meadow_placed;
    bool* quarry_placed;

public:
    VGMap();
    ~VGMap();
    const int* width;
    const int* height;
    bool placeTile(int, int, bool, BuildingTile);
	void setName(string given_name);
    int calculateScore();
    int getScore() const;
    void PrintVillageBoard();
    std::vector<vector<BuildingTile*>> *map;

};
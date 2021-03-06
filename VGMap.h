#pragma once
#include "Resources.h"
#include "VGMapLoader.h"
#include <vector>

class VGMap {
    int* score;
    int* village_number;
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
    int getVillageNum() const;
    void PrintVillageBoard();
	void PrintNumRow(int num);
    std::vector<vector<BuildingTile*>> *map;

};
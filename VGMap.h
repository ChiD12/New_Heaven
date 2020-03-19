#pragma once
#include "Resources.h"
#include "VGMapLoader.h"
#include <vector>

class VGMap {
    int* width;
    int* height;
    int* score;

    bool* forest_placed;
    bool* wheatfield__placed;
    bool* meadow_placed;
    bool* quarry_placed;

    std::vector<vector<BuildingTile*>> *map;
    //std::vector<BuildingTile*> *invalid_tiles;

public:
    VGMap();
    //VGMap(vector<vector<BuildingTile*>>);//to eventually receive a map from mapLoader
    ~VGMap();
    bool placeTile(int, int, BuildingTile);
    int calculateScore();
    void showMap();
};
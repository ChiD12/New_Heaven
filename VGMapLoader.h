#pragma once
#include <string>
#include <vector>
#include "Resources.h"
using namespace std;

/**
	VGMapLoader.h
	Purpose: Instantiates a graph (2d vector) for the Village Board that each player will have.

	@author Matt
	@version 1.0 2020-03-01
*/

class VGMapLoader {
private:
	vector<vector<BuildingTile*>> *map;

public:
	/**
		Default constructor, not used.
	*/
	VGMapLoader();
	~VGMapLoader();

	/**
		Takes a filename as input, and creates a map for the Village Board based on the contents of the file.
		The given file should be comma-separated, and contain chars T or X to represent a Tile or Invalid Tile respectively.

		@throws an error if file is not found
	*/
	void loadMap(string filename);

	/**
		@returns a copy of the generated map
		@throws an error if map is not defined (null)
	*/
	vector<vector<BuildingTile*>>& getMap();
};
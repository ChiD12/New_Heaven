#pragma once
#include <string>
#include "Resources.h"
using namespace std;

/**
	GBMapLoader.h
	Purpose: Instantiates a graph (2d vector) for the Game Board to start the game.

	@author Matt
	@version 1.0 2020-03-01
*/

class GBMapLoader {
private:

	vector<vector<Node*>>* map;

public:
	/**
		Default constructor, not used.
	*/
	GBMapLoader();
	~GBMapLoader();

	/**
		Takes a filename as input, and creates a map for the Game Board based on the contents of the file.
		The given file should be comma-separated, and contain chars N or X to represent a Node or Invalid Node respectively.
		Moreover, the "board" should be a rectangle or square. If you want some rows to have different lengths, you must fill
		the blank spaces with X (invalid nodes).

		@throws an error if file is not found
	*/
	void loadMap(int numPlayers);

	/**
		@returns a copy of the generated map
		@throws an error if map is not defined (null)
	*/
	vector<vector<Node*>>& getMap();
};
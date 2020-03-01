#pragma once
#include <vector>
#include <string>
using namespace std;

/**
	Resources.h
	Purpose: defines various resource classes (i.e. Nodes and Tiles) that will be shared among many other files:

	- A HarvestTile consists of 4 resources types, and will be divided into 4 Nodes once placed onto the Game Board.
	- The HarvestDeck will be the deck of the Harvest Tiles.
	- A Node defines 1 resource (out of 4) of a Harvest Tile. The Game Board will contain a graph of these Nodes.
	- A BuildingTile consists of 1 building type. Each player's Village Board will contain a graph of these Building Tiles.
	- A BuildingDeck will be the deck of the Building Tiles.

	@author Matt, Nathan, Zi, Daniel
	@version 1.0 2020-03-01
*/

enum resource_type { WOOD, GRAIN, SHEEP, STONE, NO_RESOURCE };
enum building_type { FOREST, WHEATFIELD, MEADOW, QUARRY, NO_BUILDING };


class HarvestTile {
private:
	resource_type upper_left;
	resource_type upper_right;
	resource_type bottom_left;
	resource_type bottom_right;

	resource_type* ul_ptr = &upper_left;
	resource_type* ur_ptr = &upper_right;
	resource_type* bl_ptr = &bottom_left;
	resource_type* br_ptr = &bottom_right;

	string upper_left_str;
	string upper_right_str;
	string bottom_left_str;
	string bottom_right_str;

	string* upper_left_str_ptr;
	string* upper_right_str_ptr;
	string* bottom_left_str_ptr;
	string* bottom_right_str_ptr;


public:
	HarvestTile();
	~HarvestTile();

	void RotateTileRight();
	void RotateTileLeft();

	void PrintHarvestTile();

};

class HarvestDeck {
private:
	int harvest_card_count;
	int* hcc_ptr = &harvest_card_count;

public:
	HarvestDeck();
	~HarvestDeck();

	int GetCardCount();

	HarvestTile DrawHarvestTile();

};


class BuildingTile {

public:
	building_type type;
	string type_representation;
	building_type* bt_ptr = &type;

	int building_value;
	int* bv_ptr = &building_value;
	int* x_index;
	int* y_index;
	bool* flipped;
	bool* valid;
	vector<BuildingTile*>* edge_list;

	void PrintBuildingTile();

	BuildingTile();

	/**
		Secondary constructor which will be used when instantiating the Village Board map

		@param x the x-coordinate of the tile
		@param y the y-coordinate of the tile
		@param valid signifies if the Building Tile is valid (default) or should be ignored
	*/
	BuildingTile(int x, int y, bool valid = 1);

	/**
		Destructor to handle Memory Leaks
	*/
	~BuildingTile();
};


class BuildingDeck {
private:
	int building_card_count;
	int* bcc_ptr = &building_card_count;

public:
	BuildingDeck();
	~BuildingDeck();
	int GetCardCount();
	BuildingTile DrawBuildingTile(); //Do the same here as I did for the DrawHarvestTile() method.

};


class Node {
public:
	int* x_index;
	int* y_index;
	resource_type type;
	resource_type* p_type = &type;
	vector<Node*>* edge_list;
	bool* valid;

	/**
		Default constructor, not used
	*/
	Node();

	/**
		Main constructor which will be used when instantiating the Game Board map

		@param x the x-coordinate of the node
		@param y the y-coordinate of Node is valid (default) or should be ignored
	*/
	Node(int x, int y, bool valid = 1);

	/**
		Destructor to handle memory leaks
	*/
	~Node();
};
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

enum building_type { FOREST, WHEATFIELD, MEADOW, QUARRY, NO_BUILDING };
enum resource_type { WOOD, GRAIN, SHEEP, STONE, NO_RESOURCE };

class HarvestTile {
public:
	resource_type* ul_ptr;
	resource_type* ur_ptr;
	resource_type* bl_ptr;
	resource_type* br_ptr;

	string* upper_left_str_ptr;
	string* upper_right_str_ptr;
	string* bottom_left_str_ptr;
	string* bottom_right_str_ptr;

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

	HarvestTile* DrawHarvestTile(); //Returns a pointer to a HarvestTile and decrements the deck count.

};


class BuildingTile {

public:
	building_type* bt_ptr;
	string* type_representation;

	int* bv_ptr;
	int* x_index;
	int* y_index;
	bool* flipped;
	bool* valid;
	vector<BuildingTile*>* edge_list;

	BuildingTile();
	~BuildingTile();
	BuildingTile(const BuildingTile&);

	/**
		Secondary constructor which will be used when instantiating the Village Board map

		@param x the x-coordinate of the tile
		@param y the y-coordinate of the tile
		@param valid signifies if the Building Tile is valid (default) or should be ignored
	*/
	BuildingTile(int x, int y, bool valid = 1);

	//BuildingTile(int x, int y, bool valid, bool am_i_flipped, building_type given_type, int value);

	void PrintBuildingTile();
};


class BuildingDeck {
private:
	int building_card_count;
	int* bcc_ptr = &building_card_count;

public:
	BuildingDeck();
	~BuildingDeck();
	int GetCardCount();
	BuildingTile* DrawBuildingTile(); //Returns a pointer to a BuildingTile and decrements the deck count.

};


class Node {
public:
	int* x_index;
	int* y_index;
	resource_type* rt_ptr;
	string* resource_rep;
	vector<Node*>* edge_list;
	bool* valid;

	Node();
	~Node();
	Node(const Node&);

	/**
		Main constructor which will be used when instantiating the Game Board map

		@param x the x-coordinate of the node
		@param y the y-coordinate of Node is valid (default) or should be ignored
	*/
	Node(int x, int y, bool valid = 1);

	/**
		TODO
	*/
	bool compare(Node rh);

	/**
		Mutator function to set the resource given, and also assign it 
		to the string representation of this node (to be used later when printing the board)
	*/
	void setResourceType(const resource_type& res);

};
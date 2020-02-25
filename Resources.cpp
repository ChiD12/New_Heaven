#include "Resources.h"
#include <string>
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>


HarvestTile::HarvestTile()
{


	int resource_selector; //Will hold a random number which will correlate to an enum.

	resource_type random_resource; //Will hold the resource which will be selected by resource_selector and will be assigned to a section of a resource tile.

	for (int i = 0; i < 4; i++) {
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
		srand(nanoseconds.count());


		resource_selector = (rand() % 4) + 1;

		string resource_string;

		switch (resource_selector) { //Use our random number to select a resource.
		case 1: random_resource = WOOD;
			resource_string = "WOOD";
			break;
		case 2: random_resource = GRAIN;
			resource_string = "GRAIN";
			break;
		case 3: random_resource = SHEEP;
			resource_string = "SHEEP";
			break;
		case 4: random_resource = STONE;
			resource_string = "STONE";
			break;
		}


		switch (i) { //Store our new random resource in its place.
		case 0: *this->ul_ptr = random_resource;
			this->upper_left_str = resource_string;
			break;
		case 1: *this->ur_ptr = random_resource;
			this->upper_right_str = resource_string;
			break;
		case 2: *this->bl_ptr = random_resource;
			this->bottom_left_str = resource_string;
			break;
		case 3: *this->br_ptr = random_resource;
			this->bottom_right_str = resource_string;
			break;
		}

	}

}

HarvestTile::~HarvestTile()
{
	this->ul_ptr = NULL;
	this->ur_ptr = NULL;
	this->bl_ptr = NULL;
	this->br_ptr = NULL;

	delete ul_ptr;
	delete ur_ptr;
	delete bl_ptr;
	delete br_ptr;

}

void HarvestTile::RotateTileRight()
{
	resource_type temp = this->upper_left;

	this->ul_ptr = this->bl_ptr;
	this->bl_ptr = this->br_ptr;
	this->br_ptr = this->ur_ptr;
	this->ur_ptr = &temp;
}

void HarvestTile::RotateTileLeft()
{

	resource_type temp = this->upper_left;

	this->ul_ptr = this->ur_ptr;
	this->ur_ptr = this->br_ptr;
	this->br_ptr = this->bl_ptr;
	this->bl_ptr = &temp;

}

void HarvestTile::PrintHarvestTile()
{
	cout << "The resources in this tile are as follows: " << this->upper_left_str << ", " << this->upper_right_str << ", " << this->bottom_left_str << ", " << this->bottom_right_str << endl;
}

HarvestDeck::HarvestDeck()
{
	*this->hcc_ptr = 60;
}

HarvestDeck::~HarvestDeck()
{
	this->hcc_ptr = NULL;
	delete hcc_ptr;
}

int HarvestDeck::GetCardCount()
{
	return this->harvest_card_count;
}

HarvestTile HarvestDeck::DrawHarvestTile()
{
	if (this->harvest_card_count < 1) {
		cout << "There are no more cards!";
	}

	else {
		this->harvest_card_count--;
		return HarvestTile();
	}

}

BuildingDeck::BuildingDeck()
{
	*this->bcc_ptr = 144;
}

BuildingDeck::~BuildingDeck()
{
	this->bcc_ptr = NULL;
	delete bcc_ptr;
}

int BuildingDeck::GetCardCount()
{
	return this->building_card_count;
}

BuildingTile::BuildingTile()
{
	int type_selector; //Will hold a random number which will correlate to an enum.
	building_type random_type; //Will hold the building type which will be selected by type_selector and will be assigned to the building tile.


	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
	srand(nanoseconds.count());
	type_selector = (rand() % 4) + 1;

	switch (type_selector) { //Use our random number to select a type.
	case 1: random_type = FOREST;
		this->type_representation = "FOREST";
		break;
	case 2: random_type = WHEATFIELD;
		this->type_representation = "WHEATFIELD";
		break;
	case 3: random_type = MEADOW;
		this->type_representation = "MEADOW";
		break;
	case 4: random_type = QUARRY;
		this->type_representation = "QUARRY";
		break;
	}

	*this->bt_ptr = random_type;
	*this->bv_ptr = (rand() % 6) + 1; //Assign a random value from 1 to 6
	x_index = new int(-1);//initializing the remaining class variables to avoid trying to delete empty class members
	y_index = new int(-1);
	this->valid = new bool(valid);
	building_value = 0;
	flipped = new bool(false);
	edge_list = vector<BuildingTile*>(4);
}


BuildingTile BuildingDeck::DrawBuildingTile()
{

	if (this->building_card_count < 1) {
		cout << "There are no more cards!";
	}

	else {
		this->building_card_count--;
		return BuildingTile();
	}
}


BuildingTile::BuildingTile(int x, int y, bool valid) {
	x_index = new int(x);
	y_index = new int(y);
	this->valid = new bool(valid);
	type = NO_BUILDING;
	building_value = 0;
	flipped = new bool(false);
	edge_list = vector<BuildingTile*>(4); // 0 is north, 1 is east, 2 is south, 3 is west
}

BuildingTile::BuildingTile(int x, int y, building_type type, bool flipped, int value) { //constructor to facilitate testing
	x_index = new int(x);
	y_index = new int(y);
	this->valid = new bool(valid);
	this->type = type;
	building_value = value;
	this->flipped = new bool(flipped);
	edge_list = vector<BuildingTile*>(4);
}

void BuildingTile::PrintBuildingTile()
{
	cout << "This is a " << this->type_representation << " tile with a value of " << this->building_value << ". " << endl;
}

BuildingTile::~BuildingTile()
{
	/*this->bv_ptr = NULL; //pointers to class members not stored in the heap will result in error when doing delete(pointer)
	this->bt_ptr = NULL;
	this->x_index = NULL;
	this->y_index = NULL;
	this->flipped = NULL;
	this->valid = NULL;
	delete bv_ptr;
	delete bt_ptr;*/
	delete(x_index);
	delete(y_index);
	delete(flipped);
	delete(valid);

	/*for (int i = 0; i < edge_list.size(); i++) { //disabled to prevent double deletion error (every valid tile is deleted at least 4 times)
		delete edge_list[i];
	}*/
}

Node::Node() {}
Node::Node(int x, int y, bool valid)
{
	x_index = new int(x);
	y_index = new int(y);
	this->valid = new bool(valid);
	type = NO_RESOURCE;
	edge_list = vector<Node*>(4); // 0 is north, 1 is east, 2 is south, 3 is west
}
Node::~Node()
{
	this->x_index = NULL;
	this->y_index = NULL;
	this->p_type = NULL;
	this->valid = NULL;
	delete x_index;
	delete y_index;
	delete p_type;
	delete valid;
	/*
	for (int i = 0; i < edge_list.size(); i++) {
		delete edge_list[i];
	}
	*/
};
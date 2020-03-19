#include "Resources.h"
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>


HarvestTile::HarvestTile()
{

	int resource_selector; //Will hold a random number which will correlate to an enum.

	resource_type random_resource; //Will hold the resource which will be selected by resource_selector and will be assigned to a section of a resource tile.

	for (int i = 0; i < 4; i++) {


		// This creates a new random seed using the system's clock which ensures that the numbers generated are more varied and random.

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
		case 0: this->ul_ptr = new resource_type(random_resource);

			this->upper_left_str_ptr = new string(resource_string);
			break;
		case 1: this->ur_ptr = new resource_type(random_resource);

			this->upper_right_str_ptr = new string(resource_string);
			break;
		case 2: this->bl_ptr = new resource_type(random_resource);
			this->bottom_left_str_ptr = new string(resource_string);
			break;
		case 3: this->br_ptr = new resource_type(random_resource);

			this->bottom_right_str_ptr = new string(resource_string);
			break;
		}
	}

}

HarvestTile::~HarvestTile()
{
	delete ul_ptr;
	delete ur_ptr;
	delete bl_ptr;
	delete br_ptr;
	delete upper_left_str_ptr;
	delete upper_right_str_ptr;
	delete bottom_left_str_ptr;
	delete bottom_right_str_ptr;

	ul_ptr = nullptr;
	ur_ptr = nullptr;
	bl_ptr = nullptr;
	br_ptr = nullptr;
	upper_left_str_ptr = nullptr;
	upper_right_str_ptr = nullptr;
	bottom_left_str_ptr = nullptr;
	bottom_right_str_ptr = nullptr;
}

void HarvestTile::RotateTileRight()
{
	resource_type temp = *ul_ptr;

	this->ul_ptr = this->bl_ptr;
	this->bl_ptr = this->br_ptr;
	this->br_ptr = this->ur_ptr;
	this->ur_ptr = &temp;
}

void HarvestTile::RotateTileLeft()
{
	resource_type temp = *ul_ptr;

	this->ul_ptr = this->ur_ptr;
	this->ur_ptr = this->br_ptr;
	this->br_ptr = this->bl_ptr;
	this->bl_ptr = &temp;
}

void HarvestTile::PrintHarvestTile()
{
	cout << "The resources in this tile are as follows: " << *this->upper_left_str_ptr << ", " << *this->upper_right_str_ptr << ", " << *this->bottom_left_str_ptr << ", " << *this->bottom_right_str_ptr << endl;
}

HarvestDeck::HarvestDeck()
{
	harvest_card_count = 60;
	hcc_ptr = &harvest_card_count;
}

HarvestDeck::~HarvestDeck() {}

int HarvestDeck::GetCardCount()
{
	return *this->hcc_ptr;
}

HarvestTile* HarvestDeck::DrawHarvestTile()
{

	if (*hcc_ptr < 1) {
		cout << "There are no more cards!";
	}

	else {

		(*hcc_ptr)--;
		HarvestTile* to_return = new HarvestTile();
		return to_return;
	}

}

BuildingDeck::BuildingDeck()
{
	building_card_count = 144;
	bcc_ptr = &building_card_count;
}

BuildingDeck::~BuildingDeck(){}

int BuildingDeck::GetCardCount() { return this->building_card_count; }

BuildingTile::BuildingTile()
{
	int type_selector; //Will hold a random number which will correlate to an enum.
	building_type random_type; //Will hold the building type which will be selected by type_selector and will be assigned to the building tile.

	/*
	 * This creates a new random seed using the system's clock which ensures that the numbers generated are more varied and random.
	 */

	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
	srand(nanoseconds.count());
	type_selector = (rand() % 4) + 1;

	switch (type_selector) { //Use our random number to select a type.
	case 1: random_type = FOREST;
		this->type_representation = new string("FOREST");
		break;
	case 2: random_type = WHEATFIELD;
		this->type_representation = new string("WHEATFIELD");
		break;
	case 3: random_type = MEADOW;
		this->type_representation = new string("MEADOW");
		break;
	case 4: random_type = QUARRY;
		this->type_representation = new string("QUARRY");
		break;
	}

	bt_ptr = new building_type(random_type);
	bv_ptr = new int((rand() % 6) + 1); //Assign a random value from 1 to 6
	x_index = new int(-1);//initializing the remaining class variables to avoid trying to delete empty class members
	y_index = new int(-1);
	this->valid = new bool(valid);
	flipped = new bool(false);
	edge_list = new vector<BuildingTile*>(4);
}

std::string typeToString(building_type type) { //added to make the longer parameterized constructor of BuildingTile more readable
	switch (type) {
	case FOREST:
		return "FOREST";
		break;
	case WHEATFIELD:
		return "WHEATFIELD";
		break;
	case MEADOW:
		return "MEADOW";
		break;
	case QUARRY:
		return "QUARRY";
		break;

	case NO_BUILDING:
		return "NO BUILDING";
		break;
	default:;
	}
}


BuildingTile* BuildingDeck::DrawBuildingTile()
{

	if (*bcc_ptr < 1) {
		cout << "There are no more cards!";
		return nullptr;
	}

	else {
		(*bcc_ptr)--;
		BuildingTile* return_me = new BuildingTile();
		return return_me;
	}
}


BuildingTile::BuildingTile(int x, int y, bool valid) {
	x_index = new int(x);
	y_index = new int(y);
	this->valid = new bool(valid);
	bt_ptr = new building_type(NO_BUILDING);
	bv_ptr = new int(NO_BUILDING);
	type_representation = new string(typeToString(NO_BUILDING));
	flipped = new bool(false);
	if (*this->valid)
		edge_list = new vector<BuildingTile*>(4); // 0 is north, 1 is east, 2 is south, 3 is weste
	else
		edge_list = new vector<BuildingTile*>(0);
}


BuildingTile::BuildingTile(int x, int y, bool valid, bool am_i_flipped, building_type given_type, int value) { //used for testing the VGMap's placeTile function
	type_representation = new string(typeToString(given_type));
	bt_ptr = new building_type(given_type);
	bv_ptr = new int(value);
	x_index = new int(x);
	y_index = new int(y);
	flipped = new bool(am_i_flipped);
	this->valid = new bool(valid);
	if (*this->valid)
		edge_list = new vector<BuildingTile*>(4); // 0 is north, 1 is east, 2 is south, 3 is weste
	else
		edge_list = new vector<BuildingTile*>(0);
}


BuildingTile::BuildingTile(const BuildingTile& tile) { 
	bt_ptr = new building_type(*tile.bt_ptr);
	type_representation = new string(*tile.type_representation);
	bv_ptr = new int(*tile.bv_ptr);
	x_index = new int(*tile.x_index);
	y_index = new int(*tile.y_index);
	flipped = new bool(*tile.flipped);
	valid = new bool(*tile.valid);
	/*
	edge_list = new vector<BuildingTile*>(tile.edge_list->size());
	
	for (int i = 0; i < tile.edge_list->size(); i++)
		edge_list->at(i) = new BuildingTile(*tile.edge_list->at(i));
		*/
	edge_list = tile.edge_list;
}


BuildingTile& BuildingTile::operator=(const BuildingTile& tile) {
	bt_ptr = new building_type(*tile.bt_ptr);
	type_representation = new string(*tile.type_representation);
	bv_ptr = new int(*tile.bv_ptr);
	x_index = new int(*tile.x_index);
	y_index = new int(*tile.y_index);
	flipped = new bool(*tile.flipped);
	valid = new bool(*tile.valid);
	edge_list = tile.edge_list;
	return *this;
}


void BuildingTile::PrintBuildingTile()
{
	cout << "This is a " << *this->type_representation << " tile with a value of " << *bv_ptr << ". " << endl;
}


BuildingTile::~BuildingTile()
{
	delete bt_ptr;
	delete x_index;
	delete y_index;
	delete flipped;
	delete valid;
	
	bv_ptr = nullptr;
	bt_ptr = nullptr;
	x_index = nullptr;
	y_index = nullptr;
	flipped = nullptr;
	valid = nullptr;
}


Node::Node() {}
Node::Node(int x, int y, bool is_valid)
{
	x_index = new int(x);
	y_index = new int(y);
	valid = new bool(is_valid);
	rt_ptr = new resource_type(NO_RESOURCE);
	resource_rep = new string("[EMPTY]");
	if (*valid)
		edge_list = new vector<Node*>(4); // 0 is north, 1 is east, 2 is south, 3 is west
	else 
		edge_list = new vector<Node*>(0);
}


Node::Node(const Node& node) {
	rt_ptr = new resource_type(*node.rt_ptr);
	resource_rep = new string(*node.resource_rep);
	x_index = new int(*node.x_index);
	y_index = new int(*node.y_index);
	valid = new bool(*node.valid);
	edge_list = node.edge_list; //this shallow copy is done intentionally as the edgelist should always point to the same connection on the game board
}


Node& Node::operator=(const Node& node) {
	rt_ptr = new resource_type(*node.rt_ptr);
	resource_rep = new string(*node.resource_rep);
	x_index = new int(*node.x_index);
	y_index = new int(*node.y_index);
	valid = new bool(*node.valid);
	edge_list = node.edge_list;
	return *this;
}


void Node::setResourceType(const resource_type& res) {
	*rt_ptr = res;

	switch (res) { 
	case WOOD: *resource_rep = "[WOOD]";
		break;
	case GRAIN: *resource_rep = "[GRAIN]";
		break;
	case SHEEP: *resource_rep = "[SHEEP]";
		break;
	case STONE: *resource_rep = "[STONE]";
		break;
	default: *resource_rep = "[EMPTY]";
	}
}


bool Node::compare(Node rh) {

	if (*(x_index) == *(rh.x_index)) {

		if (*(y_index) == *(rh.y_index)) {

			if (*(rt_ptr) == *(rh.rt_ptr)) {
				return true;
			}
		}
	}
	return false;
}


Node::~Node()
{
	delete x_index;
	delete y_index;
	delete rt_ptr;
	delete valid;
	x_index = nullptr;
	y_index = nullptr;
	rt_ptr = nullptr;
	valid = nullptr;
};
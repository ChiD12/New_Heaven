#include "Resources.h"
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
HarvestTile::HarvestTile() {
	ul_ptr = new resource_type(NO_RESOURCE);
	ur_ptr = new resource_type(NO_RESOURCE);
	bl_ptr = new resource_type(NO_RESOURCE);
	br_ptr = new resource_type(NO_RESOURCE);

	upper_left_str_ptr = new string("[E]");
	upper_right_str_ptr = new string("[E]");
	bottom_left_str_ptr = new string("[E]");
	bottom_right_str_ptr = new string("[E]");
}

string typeToString(resource_type given_type) {
	switch (given_type) {
	case WOOD:
		return "[W]";
		break;
	case GRAIN:
		return "[G]";
		break;
	case SHEEP:
		return "[S]";
		break;
	case STONE:
		return "[T]";
		break;
	default:
		return "[E]";
		break;
	}
	
}

HarvestTile::HarvestTile(bool given_bool)
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
			resource_string = "[W]";
			break;
		case 2: random_resource = GRAIN;
			resource_string = "[G]";
			break;
		case 3: random_resource = SHEEP;
			resource_string = "[S]";
			break;
		case 4: random_resource = STONE;
			resource_string = "[T]";
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

HarvestTile::HarvestTile(int ul, int ur, int bl, int br)
{
	resource_type first = static_cast<resource_type>(ul);
	resource_type second = static_cast<resource_type>(ur);
	resource_type third = static_cast<resource_type>(bl);
	resource_type fourth = static_cast<resource_type>(br);

	ul_ptr = new resource_type(first);
	ur_ptr = new resource_type(second);
	bl_ptr = new resource_type(third);
	br_ptr = new resource_type(fourth);

	upper_left_str_ptr = new string(typeToString(first));
	upper_right_str_ptr = new string(typeToString(second));
	bottom_left_str_ptr = new string(typeToString(third));
	bottom_right_str_ptr = new string(typeToString(fourth));
}

HarvestTile::HarvestTile(const HarvestTile &given_tile)
{
	ul_ptr = new resource_type(*given_tile.ul_ptr);
	ur_ptr = new resource_type(*given_tile.ur_ptr);
	bl_ptr = new resource_type(*given_tile.bl_ptr);
	br_ptr = new resource_type(*given_tile.br_ptr);

	upper_left_str_ptr = new string(*given_tile.upper_left_str_ptr);
	upper_right_str_ptr = new string(*given_tile.upper_right_str_ptr);
	bottom_left_str_ptr = new string(*given_tile.bottom_left_str_ptr);
	bottom_right_str_ptr = new string(*given_tile.bottom_right_str_ptr);
}

HarvestTile & HarvestTile::operator=(const HarvestTile & given_tile)
{
	ul_ptr = new resource_type(*given_tile.ul_ptr);
	ur_ptr = new resource_type(*given_tile.ur_ptr);
	bl_ptr = new resource_type(*given_tile.bl_ptr);
	br_ptr = new resource_type(*given_tile.br_ptr);

	upper_left_str_ptr = new string(*given_tile.upper_left_str_ptr);
	upper_right_str_ptr = new string(*given_tile.upper_right_str_ptr);
	bottom_left_str_ptr = new string(*given_tile.bottom_left_str_ptr);
	bottom_right_str_ptr = new string(*given_tile.bottom_right_str_ptr);

	return *this;
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
	std::cout << "Rotating Right..." << endl;
	resource_type* temp = ul_ptr;

	this->ul_ptr = this->bl_ptr;
	this->bl_ptr = this->br_ptr;
	this->br_ptr = this->ur_ptr;
	this->ur_ptr = temp;

	string* temp_string = this->upper_left_str_ptr;
	this->upper_left_str_ptr = this->bottom_left_str_ptr;
	this->bottom_left_str_ptr = this->bottom_right_str_ptr;
	this->bottom_right_str_ptr = this->upper_right_str_ptr;
	this->upper_right_str_ptr = temp_string;
}

void HarvestTile::RotateTileLeft()
{
	std::cout << "Rotating Left..." << endl;
	resource_type* temp = ul_ptr;

	this->ul_ptr = this->ur_ptr;
	this->ur_ptr = this->br_ptr;
	this->br_ptr = this->bl_ptr;
	this->bl_ptr = temp;

	string* temp_string = this->upper_left_str_ptr;
	this->upper_left_str_ptr = this->upper_right_str_ptr;
	this->upper_right_str_ptr = this->bottom_right_str_ptr;
	this->bottom_right_str_ptr = this->bottom_left_str_ptr;
	this->bottom_left_str_ptr = temp_string;
}

void HarvestTile::PrintHarvestTile()
{
	cout << *this->upper_left_str_ptr << *this->upper_right_str_ptr << endl;
	cout << *this->bottom_left_str_ptr << *this->bottom_right_str_ptr << endl;
}


HarvestDeck::HarvestDeck()
{
	harvest_card_count = new int(60);
	harvest_deck = new vector<HarvestTile>(60);
	harvest_deck->at(0) = HarvestTile(3, 1, 0, 0);
	harvest_deck->at(1) = HarvestTile(1, 3, 1, 1);
	harvest_deck->at(2) = HarvestTile(2, 0, 0, 2);
	harvest_deck->at(3) = HarvestTile(3, 0, 0, 3);
	harvest_deck->at(4) = HarvestTile(0, 2, 3, 0);
	harvest_deck->at(5) = HarvestTile(3, 0, 1, 2);
	harvest_deck->at(6) = HarvestTile(2, 2, 1, 0);
	harvest_deck->at(7) = HarvestTile(3, 2, 0, 1);
	harvest_deck->at(8) = HarvestTile(3, 2, 0, 3);
	harvest_deck->at(9) = HarvestTile(0, 2, 1, 3);
	harvest_deck->at(10) = HarvestTile(0, 0, 0, 0);
	harvest_deck->at(11) = HarvestTile(2, 1, 3, 3);
	harvest_deck->at(12) = HarvestTile(1, 3, 2, 3);
	harvest_deck->at(13) = HarvestTile(0, 2, 1, 2);
	harvest_deck->at(14) = HarvestTile(3, 1, 0, 1);
	harvest_deck->at(15) = HarvestTile(0, 0, 2, 0);
	harvest_deck->at(16) = HarvestTile(1, 1, 3, 0);
	harvest_deck->at(17) = HarvestTile(3, 2, 1, 2);
	harvest_deck->at(18) = HarvestTile(3, 1, 3, 3);
	harvest_deck->at(19) = HarvestTile(0, 3, 1, 2);
	harvest_deck->at(20) = HarvestTile(2, 0, 2, 1);
	harvest_deck->at(21) = HarvestTile(2, 3, 2, 3);
	harvest_deck->at(22) = HarvestTile(0, 0, 2, 0);
	harvest_deck->at(23) = HarvestTile(2, 1, 3, 1);
	harvest_deck->at(24) = HarvestTile(3, 3, 2, 2);
	harvest_deck->at(25) = HarvestTile(3, 3, 0, 0);
	harvest_deck->at(26) = HarvestTile(1, 2, 2, 3);
	harvest_deck->at(27) = HarvestTile(3, 1, 2, 1);
	harvest_deck->at(28) = HarvestTile(0, 1, 1, 1);
	harvest_deck->at(29) = HarvestTile(2, 3, 0, 0);
	harvest_deck->at(30) = HarvestTile(1, 2, 2, 2);
	harvest_deck->at(31) = HarvestTile(2, 1, 0, 1);
	harvest_deck->at(32) = HarvestTile(0, 2, 3, 3);
	harvest_deck->at(33) = HarvestTile(2, 1, 1, 0);
	harvest_deck->at(34) = HarvestTile(1, 1, 1, 2);
	harvest_deck->at(35) = HarvestTile(2, 2, 1, 0);
	harvest_deck->at(36) = HarvestTile(3, 0, 2, 0);
	harvest_deck->at(37) = HarvestTile(3, 1, 1, 0);
	harvest_deck->at(38) = HarvestTile(1, 0, 2, 2);
	harvest_deck->at(39) = HarvestTile(2, 1, 3, 2);
	harvest_deck->at(40) = HarvestTile(1, 1, 1, 0);
	harvest_deck->at(41) = HarvestTile(1, 0, 3, 0);
	harvest_deck->at(42) = HarvestTile(1, 0, 0, 2);
	harvest_deck->at(43) = HarvestTile(3, 2, 2, 3);
	harvest_deck->at(44) = HarvestTile(2, 3, 0, 3);
	harvest_deck->at(45) = HarvestTile(3, 3, 2, 3);
	harvest_deck->at(46) = HarvestTile(3, 3, 1, 1);
	harvest_deck->at(47) = HarvestTile(2, 1, 1, 0);
	harvest_deck->at(48) = HarvestTile(2, 2, 1, 3);
	harvest_deck->at(49) = HarvestTile(3, 0, 0, 3);
	harvest_deck->at(50) = HarvestTile(1, 2, 1, 3);
	harvest_deck->at(51) = HarvestTile(1, 2, 3, 3);
	harvest_deck->at(52) = HarvestTile(0, 2, 3, 2);
	harvest_deck->at(53) = HarvestTile(0, 1, 0, 0);
	harvest_deck->at(54) = HarvestTile(1, 2, 1, 3);
	harvest_deck->at(55) = HarvestTile(3, 2, 3, 2);
	harvest_deck->at(56) = HarvestTile(0, 2, 0, 1);
	harvest_deck->at(57) = HarvestTile(3, 3, 1, 0);
	harvest_deck->at(58) = HarvestTile(2, 1, 1, 2);
	harvest_deck->at(59) = HarvestTile(1, 0, 2, 3);
	
	
}

HarvestDeck::HarvestDeck(const HarvestDeck & given_deck)
{
	harvest_card_count = new int(*given_deck.harvest_card_count);
	harvest_deck = new vector<HarvestTile>(*given_deck.harvest_deck);
}

HarvestDeck & HarvestDeck::operator=(const HarvestDeck & given_deck)
{
	harvest_card_count = new int(*given_deck.harvest_card_count);
	harvest_deck = new vector<HarvestTile>(*given_deck.harvest_deck);

	return *this;
}

HarvestDeck::~HarvestDeck() {
	delete harvest_card_count;
	harvest_card_count = nullptr;
	harvest_deck->clear();
	harvest_deck = nullptr;
}

int HarvestDeck::GetCardCount()
{
	return *this->harvest_card_count;
}

HarvestTile* HarvestDeck::DrawHarvestTile()
{

	if (*harvest_card_count < 1) {
		cout << "There are no more tiles!";
	}

	else {

		(*harvest_card_count)--;
		HarvestTile* to_return = new HarvestTile(harvest_deck->back());
		harvest_deck->pop_back();
		cout << "There are now " << this->GetCardCount() << " tiles left in the harvest deck." << endl;
		return to_return;
	}

}

BuildingDeck::BuildingDeck() //FOREST, WHEATFIELD, MEADOW, QUARRY
{
	building_card_count = new int(144);
	building_deck = new vector<BuildingTile>(144);
	int counter = 0;
	int value_rep = 1;
	int type_rep = 1;

	while (counter < 144) {
		if (type_rep == 1) {
			building_deck->at(counter) = (BuildingTile(FOREST, value_rep));
			value_rep++;
			type_rep++;
			counter++;
			if (value_rep == 7)
				value_rep = 1;
			continue;
		}
		if (type_rep == 2) {
			building_deck->at(counter) = (BuildingTile(WHEATFIELD, value_rep));
			value_rep++;
			type_rep++;
			counter++;
			if (value_rep == 7)
				value_rep = 1;
			continue;
		}
		if (type_rep == 3) {
			building_deck->at(counter) = (BuildingTile(MEADOW, value_rep));
			value_rep++;
			type_rep++;
			counter++;
			if (value_rep == 7)
				value_rep = 1;
			continue;
		}
		if (type_rep == 4) {
			building_deck->at(counter) = (BuildingTile(QUARRY, value_rep));
			value_rep++;
			type_rep = 1;
			counter++;
			if (value_rep == 7)
				value_rep = 1;
			continue;
		}

	}
	
}

BuildingDeck::BuildingDeck(const BuildingDeck & given_deck)
{
	building_card_count = new int(*given_deck.building_card_count);
	building_deck = new vector<BuildingTile>(*given_deck.building_deck);
}

BuildingDeck & BuildingDeck::operator=(const BuildingDeck & given_deck)
{
	building_card_count = new int(*given_deck.building_card_count);
	building_deck = new vector<BuildingTile>(*given_deck.building_deck);

	return *this;
}


BuildingDeck::~BuildingDeck(){
	delete building_card_count;
	building_deck->clear();
	building_card_count = nullptr;
	building_deck = nullptr;
}
int BuildingDeck::GetCardCount() { return *this->building_card_count; }

BuildingTile::BuildingTile()
{
	bt_ptr = new building_type(NO_BUILDING);
	bv_ptr = new int(0);
	x_index = new int(-1);//initializing the remaining class variables to avoid trying to delete empty class members
	y_index = new int(-1);
	this->valid = new bool(valid);
	flipped = new bool(false);
	edge_list = new vector<BuildingTile*>(4);

	/*
	int type_selector; //Will hold a random number which will correlate to an enum.
	building_type random_type; //Will hold the building type which will be selected by type_selector and will be assigned to the building tile.
	
	 * This creates a new random seed using the system's clock which ensures that the numbers generated are more varied and random.

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
	*/
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

BuildingTile::BuildingTile(building_type given_type, int given_value)
{
	bt_ptr = new building_type(given_type); //Set the type
	bv_ptr = new int(given_value); //Set the value
	type_representation = new string(typeToString(given_type));
	x_index = new int(-1);//initializing the remaining class variables to avoid trying to delete empty class members
	y_index = new int(-1);
	this->valid = new bool(valid);
	flipped = new bool(false);
	edge_list = new vector<BuildingTile*>(4);
}

BuildingTile* BuildingDeck::DrawBuildingTile()
{

	if (*building_card_count < 1) {
		cout << "There are no more tiles!";
		return nullptr;
	}

	else {
		(*building_card_count)--;
		BuildingTile* return_me = new BuildingTile(building_deck->back());
		building_deck->pop_back();
		cout << "There are now " << this->GetCardCount() << " tiles left in the building deck." << endl;
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
	cout << "[" << *this->type_representation << "][" << *bv_ptr << "]";
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
	resource_rep = new string("[E]");
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
	case WOOD: *resource_rep = "[W]";
		break;
	case GRAIN: *resource_rep = "[G]";
		break;
	case SHEEP: *resource_rep = "[S]";
		break;
	case STONE: *resource_rep = "[T]";
		break;
	default: *resource_rep = "[E]";
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
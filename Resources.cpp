#include "Resources.h"
#include <string>
#include <iostream>
#include <math.h>


HarvestTile::HarvestTile()
{
	int resource_selector; //Will hold a random number which will correlate to an enum.

	resource_type random_resource; //Will hold the resource which will be selected by resource_selector and will be assigned to a section of a resource tile.

	for (int i = 0; i < 4; i++) {
		resource_selector = rand() % 5;

		switch (resource_selector) { //Use our random number to select a resource.
		case 1: random_resource = WOOD;
			break;
		case 2: random_resource = GRAIN;
			break;
		case 3: random_resource = SHEEP;
			break;
		case 4: random_resource = STONE;
			break;
		}
		switch (i) { //Store our new random resource in its place.
		case 0: *this->ul_ptr = random_resource;
			break;
		case 1: *this->ur_ptr = random_resource;
			break;
		case 2: *this->bl_ptr = random_resource;
			break;
		case 3: *this->br_ptr = random_resource;
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

HarvestDeck::HarvestDeck()
{
	*this->hcc_ptr = 60;
}

HarvestDeck::~HarvestDeck()
{
	this->hcc_ptr = NULL;
	delete hcc_ptr;
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

BuildingTile::BuildingTile()
{
	int type_selector; //Will hold a random number which will correlate to an enum.
	building_type random_type; //Will hold the building type which will be selected by type_selector and will be assigned to the building tile.


	type_selector = rand() % 5;

	switch (type_selector) { //Use our random number to select a type.
	case 1: random_type = FOREST;
		break;
	case 2: random_type = WHEATFIELD;
		break;
	case 3: random_type = MEADOW;
		break;
	case 4: random_type = QUARRY;
		break;
	}

	*this->bt_ptr = random_type;
	*this->bv_ptr = rand() % 7; //Assign a random value from 1 to 6

}

BuildingTile::BuildingTile(int x, int y, bool valid) {
	x_index = new int(x);
	y_index = new int(y);
	this->valid = new bool(valid);
	type = NO_BUILDING;
	edge_list = vector<BuildingTile*>(4); // 0 is north, 1 is east, 2 is south, 3 is west
}

BuildingTile::~BuildingTile()
{
	this->bv_ptr = NULL;
	this->bt_ptr = NULL;
	this->x_index = NULL;
	this->y_index = NULL;
	this->flipped = NULL;
	this->valid = NULL;
	delete bv_ptr;
	delete bt_ptr;
	delete x_index;
	delete y_index;
	delete flipped;
	delete valid;

	for (int i = 0; i < edge_list.size(); i++) {
		delete edge_list[i];
	}
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

	for (int i = 0; i < edge_list.size(); i++) {
		delete edge_list[i];
	}
}
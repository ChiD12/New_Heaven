#pragma once
#include "VGMap.h"
#include "Resources.h"
#include <iostream>

VGMap::VGMap() { //independent constructor
	const int height = 6;
	const int width = 5;
	this->height = new int(height);
	this->width = new int(width);
	score = new int(0);

	forest_placed = new bool(false);
	wheatfield__placed = new bool(false);
	meadow_placed = new bool(false);
	quarry_placed = new bool(false);

	BuildingTile* sample_element = new BuildingTile(0,0,false); //map, invalid tiles, vector allocation
	vector<BuildingTile*> temp_row(height, sample_element);
	vector<BuildingTile*> temp_invalid_tiles((height+width)*2, sample_element); //work around for double deletion problem
	vector<vector<BuildingTile*>> temp_map (width, temp_row);
	delete(sample_element);

	int i, j = 0;

	for (i=0; i < *this->width;i++) { //initializing a vector of 5 vectors each holding 6 BuildingTile, with y corresponding to inner vector index and x corresponding to outer vector index
		for (j=0; j < *this->height; j++) {
			temp_map[i][j] = new BuildingTile(i, j, true);
		}
	}

	for (i=0; i < *this->width; i++) { //initializizng each BuildingTile's adjacency list [east][north][west][south]
		for (j=0; j < *this->height; j++) {
			switch (i) {
			case 0://eastern edge of the map
				temp_map[i][j]->edge_list[3] = new BuildingTile(i-1,j,false);//everything east of each need a invalid building tile placeholder, [-1][X] in the 2D vector
				invalid_tiles.push_back(temp_map[i][j]->edge_list[3]); //work around for double deletion problem
				temp_map[i][j]->edge_list[1] = temp_map[i+1][j];
				break;
			case width-1://western edge of the map
				temp_map[i][j]->edge_list[3] = temp_map[i-1][j];
				temp_map[i][j]->edge_list[1] = new BuildingTile(i+1, j, false);//invalid placeholder to west, [max_size-1][X]
				invalid_tiles.push_back(temp_map[i][j]->edge_list[1]);
				break;
			default:
				temp_map[i][j]->edge_list[3] = temp_map[i-1][j];
				temp_map[i][j]->edge_list[1] = temp_map[i+1][j];
				break;
			}

			switch (j) {
			case 0://northern edge of the map
				temp_map[i][j]->edge_list[0] = new BuildingTile(i, j-1, false);//invalid placeholder to north, [X][-1]
				invalid_tiles.push_back(temp_map[i][j]->edge_list[0]);
				temp_map[i][j]->edge_list[2] = temp_map[i][j+1];
				break;
			case height-1://southern edge of the map
				temp_map[i][j]->edge_list[0] = temp_map[i][j-1];
				temp_map[i][j]->edge_list[2] = new BuildingTile(i,j + 1, false);//invalide placeholder to south, [X][max_size-1]
				invalid_tiles.push_back(temp_map[i][j]->edge_list[2]);
				break;
			default:
				temp_map[i][j]->edge_list[0] = temp_map[i][j-1];
				temp_map[i][j]->edge_list[2] = temp_map[i][j+1];
				break;
			}

		}
	}

	this->map = temp_map;
		
}

VGMap::VGMap(vector<vector<BuildingTile*>> map) { //constructor working with VGMapLoader
	height = new int(map[0].size());
	width = new int(map.size());
	score = new int(0);

	forest_placed = new bool(false);
	wheatfield__placed = new bool(false);
	meadow_placed = new bool(false);
	quarry_placed = new bool(false);

	BuildingTile* sample_element = new BuildingTile(0, 0, false); //map, invalid tiles, vector allocation
	vector<BuildingTile*> temp_invalid_tiles(*height * *width, sample_element); //work around for double deletion problem
	delete(sample_element);

	int i = 0;

	for (i = 0; i < *width;i++) {
		temp_invalid_tiles.push_back(map[i + 1][0]->edge_list[0]);//storing the invalid building tiles adjacent to the north and south edges
		temp_invalid_tiles.push_back(map[i + 1][*height - 1]->edge_list[2]);
	}

	for (i = 0; i < *height; i++) {
		temp_invalid_tiles.push_back(map[0][i]->edge_list[1]);//storing the invalid building tiles adjacent to the west and east edges
		temp_invalid_tiles.push_back(map[*height - 1][i]->edge_list[3]);
	}

	this->map = map;
	invalid_tiles = temp_invalid_tiles;
}

VGMap::~VGMap() { //destructor
	delete(height, width, score, forest_placed, wheatfield__placed, meadow_placed, quarry_placed);
	for (vector<BuildingTile*> row: map) {
		for (BuildingTile* element : row) {
			delete(element);
		}
	}
	for (BuildingTile* tile: invalid_tiles) { //work around for double deletion problem
		delete(tile);
	}
}

bool VGMap::placeTile(int x, int y, BuildingTile new_tile) { //method to place building, check for coordinate validity, score requirement and presence of adjacent same-typed building tile (if necessary)
	if (x < *width && x>=0 && y < *height && y>=0
		&& (*map[x][y]->bt_ptr == NO_BUILDING)
		&& (*new_tile.bv_ptr == y+1 || *new_tile.flipped == true)) {

		bool type_already_placed = false;
		building_type type = *new_tile.bt_ptr;

		switch (type) {
		case FOREST:;
			type_already_placed = *forest_placed;
			break;
		case WHEATFIELD:;
			type_already_placed = *wheatfield__placed;
			break;
		case MEADOW:
			type_already_placed = *meadow_placed;
			break;
		case QUARRY:;
			type_already_placed = *quarry_placed;
			break;
		default:;
		}
		
		if (type_already_placed) {
			//int neighbors = map[0][0]->edge_list.size(); //in case we need more than 4 indices in edge_list
			int i = 0;
			for (i = 0; i < 3; i++) {
				if (*map[x][y]->edge_list[i]->bt_ptr == type) {
					//delete(map[x][y]->bt_ptr); //in case if building type need to be stored in the CPP heap
					map[x][y]->type = type;
					*map[x][y]->flipped = *new_tile.flipped;
					return true;
				}	
			}
			std::cout << "\nneed to be placed adjacent to a tile of same type\n";
			return false;
		}
		else {
			map[x][y]->type = type;
			*map[x][y]->flipped = *new_tile.flipped;

			switch (type) {
			case FOREST:;
				*forest_placed = true;
				break;
			case WHEATFIELD:;
				*wheatfield__placed = true;
				break;
			case MEADOW:
				*meadow_placed = true;
				break;
			case QUARRY:;
				*quarry_placed=true;
				break;
			default:;
			}

			return true;
		}
	}
	else {
		std::cout << "invalid coordinate or point requirement";
		return false;
	}
}
int VGMap::calculateScore() {
	int score = 0;
	int i = 0;
	int j = 0;
	bool continuous = false;
	bool bonus = false;

	for (i = 0; i < *width;i++) {//counting through the columns
		continuous = true;
		bonus = true;

		for (j = 0; j < *height; j++) {
			if (map[i][j]->type==NO_BUILDING) {
				continuous = false;
			}
			if (*map[i][j]->flipped == true){
				bonus = false;
			}
		}

		if (!(i > (*width / 2))) { //score for each subsequent column decreases before reaching middle column
			if (continuous) {
				score += *width - i;
			}
			if (bonus) {
				score += *width - i;
			}
		}
		else { //score increases for every next column after middle column
			if (continuous) {
				score += i+1;
			}
			if (bonus) {
				score += i+1;
			}
		}
		
	}

	for (i = *height - 1; i >= 0; i--) { //counting down the rows
		continuous = true;
		bonus = true;

		for (j = 0; j < *width; j++) {
			if (map[j][i]->type == NO_BUILDING) {
				continuous = false;
			}
			if (*map[j][i]->flipped == true) {
				bonus = false;
			}
		}

		if (continuous) {
			score += i+1;
		}
		if (bonus) {
			score += i+1;
		}
		
	}
	return score;
}

void VGMap::showMap() {
	int row = 0;
	int column = 0;

	std::cout << "\n";
	for (row = 0; row < *height; row++) {
		for (column = *width-1; column >= 0; column--) {

			switch (map[column][row]->type) {
			case FOREST:;
				std::cout << "F, ";
				break;
			case WHEATFIELD:;
				std::cout << "W, ";
				break;
			case MEADOW:
				std::cout << "M, ";
				break;
			case QUARRY:
				std::cout << "Q, ";
				break;
			case NO_BUILDING:
				std::cout << "X, ";
				break;
			default:
				std::cout<< "E, ";
				break;
			}
		}
		std::cout << "\n";
	}

	//std::cout << "\nsize is " << map.size() << " x " << map[0].size()<<"\n";

	/*for (vector<BuildingTile*> row : map) {
		for (BuildingTile* element : row){
			switch (*element->bt_ptr) {
			case FOREST:;
				std::cout << "F, ";
				break;
			case WHEATFIELD:;
				std::cout << "W, ";
				break;
			case MEADOW:
				std::cout << "M, ";
				break;
			case QUARRY:;
				std::cout << "Q, ";
				break;
			case NO_BUILDING:
				std::cout << "X, ";
				break;
			default:
				std::cout << "E, ";
				break;
			}
		}
		std::cout << "\n";
	}*/
}
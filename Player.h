#pragma once
#include <string>
#include <vector>
#include "Resources.h"
#include "GBMap.h"
#include "VGMap.h"

/**
 * Purpose: Defines the player and resource handler classes. The player will hold a ResourceHandler which will keep track of the total number of resources a player can use at any given time.
 * A player contains many different data members, including a name to identify them, 2 hands of tiles, a village board, and the resource handler previously mentioned.
 * The player will be able to use various methods to manipulate their hands, the decks, their village board, and the game board.
 *
 * @author Matt, Nathan, Zi, Daniel
 * @version 1.0 2020-03-01
 */

using namespace std;


class Player {
public:
	
	std::string* name;

	vector<BuildingTile*>* building_hand; //The player's hand of buildings.

	vector<HarvestTile*>* harvest_hand; //The player's hand of harvest tiles.

	VGMap* player_board; //The player's village board.


	int* id = new int(0); //TODO add id to constructors/destructors

	Player(std::string name, int given_id,  HarvestDeck given_hdeck, BuildingDeck given_bdeck);

	~Player();

	void exchange(GBMap* given_board, int given_x, int given_y); //Picks a point on the game board, calculates the resources, and then moves the resource markers on the game board.

	bool PlaceHarvestTile(GBMap* given_board, HarvestTile* given_tile, int tl_x, int tl_y); //Given a game board and tile (pointer), place that tile onto the game board and calculate the resources acquired.

	void DrawBuilding(int number_of_cards, BuildingDeck given_deck); //Draw a building tile from the deck and add it to the hand vector.

	void DrawHarvestTile(int number_of_cards, HarvestDeck given_deck); //Draw a harvest tile from the deck and add it to the hand vector.

	void ResourceTracker(); //Can be called at any time to show which resources the player currently has in their possession.

	void BuildVillage(int given_x, int given_y, BuildingTile given_tile); //Given a building tile, place that building tile at this index on the player's village board.

	void CalculateResources(GBMap* given_board, int tl_x, int tl_y); //Used in conjunction with PlaceHarvestTile(). Will calculate the resources starting from the index given.

	void PrintHarvestHand();

	void PrintBuildingHand();
};


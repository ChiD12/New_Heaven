#include <iostream>
#include "GBMap.h"
#include "Player.h"


int main() {

	GBMap* game_board = new GBMap(4);

	BuildingDeck building_deck = BuildingDeck();

	cout << "building deck created with " << building_deck.GetCardCount() << " cards." << endl;

	HarvestDeck harvest_deck = HarvestDeck();

	cout << "harvest deck created with " << harvest_deck.GetCardCount() << " cards." << endl;

	Player richard_ham = Player("Richard", harvest_deck, building_deck);

	cout << "player created" << endl;

	richard_ham.PrintHarvestHand();
	richard_ham.PrintBuildingHand();

	HarvestTile* harvest_tile_ptr = new HarvestTile();

	richard_ham.ResourceTracker();

	cout << "\nPrinting the game board.." << endl;

	(*game_board).PrintBoard();

	cout << "Attempting to place a tile on the game board.." << endl;

	richard_ham.PlaceHarvestTile(game_board, harvest_tile_ptr, 0, 2);

	cout << "Printing the game board again.." << endl;

	(*game_board).PrintBoard();

	richard_ham.ResourceTracker();


	cout << "Printing this player's village board: " << endl;

	richard_ham.player_board->showMap();

	cout << richard_ham.name << " is placing a building tile onto their village board.." << endl;

	BuildingTile* temp_tile = new BuildingTile(1, 1, true, false, MEADOW, 2);
	BuildingTile* temp_tile1 = new BuildingTile(1, 1, true, false, MEADOW, 2);
	BuildingTile* temp_tile2 = new BuildingTile(1, 1, true, false, MEADOW, 2);
	BuildingTile* temp_tile3 = new BuildingTile(1, 1, true, false, MEADOW, 2);
	BuildingTile* temp_tile4 = new BuildingTile(1, 1, true, false, MEADOW, 2);

	richard_ham.BuildVillage(0, 1, *temp_tile);
	richard_ham.player_board->showMap();
	richard_ham.BuildVillage(1, 1, *temp_tile1);
	richard_ham.player_board->showMap();
	richard_ham.BuildVillage(2, 1, *temp_tile2);
	richard_ham.BuildVillage(3, 1, *temp_tile3);
	richard_ham.player_board->showMap();
	richard_ham.BuildVillage(4, 1, *temp_tile4);
	richard_ham.player_board->showMap();

	std::cout << "player score is: " << richard_ham.player_board->calculateScore() << endl;
	
	system("pause");

}
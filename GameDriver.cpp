#include "GameDriver.h"
#include <limits.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	gameStart();

	bool gameEnd = false;

	int turnCounter = findFirstPlayer();

	while (!gameEnd) {
		int turn = turnCounter % numOfPlayers;

		cout << endl;
		cout << "*************************************************************" << endl;
		cout << "It is **" << *(players[turn]->name) << "'s** turn" << endl;

		//print outs to place harvest tile
		cout << "The current Board State is: " << endl;
		gameBoard->PrintBoard();
		cout << endl;
		cout << "You currently are holding these Harvest Tiles: " << endl;
		players[turn]->PrintHarvestHand();

		promptHarvestTilePlacement(turn);
		cout << endl;
		cout << "***************************************************************" << endl;
		gameBoard->PrintBoard();

		remainingTiles--;
		cout << endl;


		//begin the loop for players to place their village tiles, frst the current turn player gets to place as many tiles as they want
		//then the rest of the players gets a turn to try to use the remaining resources to play as many village tiles as they wish
		for (int i = 0; i < numOfPlayers; i++) {
			int clockwisePlayers = (turn + i) % numOfPlayers;

			//Printouts for information about current game state
			cout << "**************************************************************" << endl;
			cout << "and **" << *(players[clockwisePlayers]->name) << "'s** village board is: " << endl;
			players[clockwisePlayers]->player_board->PrintVillageBoard();
			gameBoard->PrintResources();
			players[clockwisePlayers]->PrintBuildingHand();
			cout << endl;
			cout << "**" << *(players[clockwisePlayers]->name) << "** do you wish to place a village tile with remaining resources? (y or n)";
			string response;
			cin >> response;

			//if current player wishes to build, then promt them for where, and thenreprint the board and ask if they wish to build again
			//if not then next player gets a turn to build
			while (response.compare("y") == 0) {
				promptBuildingTilePlacement(clockwisePlayers);

				players[clockwisePlayers]->player_board->PrintVillageBoard();
				gameBoard->PrintResources();
				players[clockwisePlayers]->PrintBuildingHand();
				cout << "**" << *(players[clockwisePlayers]->name) << "** do you wish to place a village tile with remaining resources? (y or n)" << endl;
				cin >> response;
			}
		}

		drawVillage(turn);
		players[turn]->DrawHarvestTile(1, harvest_deck);

		//reset resources on the board
		*(gameBoard->RMWood) = 0;
		*(gameBoard->RMStone) = 0;
		*(gameBoard->RMSheep) = 0;
		*(gameBoard->RMGrain) = 0;

		turnCounter++;
		if (remainingTiles < 1) {
			gameEnd = true;
		}
	}
	computeGameScore();
}


void gameStart() {

	cout << "Starting game!" << endl;
	cout << "How many people will be playing today?: ";
	cin >> numOfPlayers;
	cout << "Great! You've chosen to play with " << numOfPlayers << " players." << endl;

	gameBoard = new GBMap(numOfPlayers);

	HarvestTile* starter_tile_1 = new HarvestTile(3, 2, 0, 0);
	HarvestTile* starter_tile_2 = new HarvestTile(1, 2, 1, 0);
	HarvestTile* starter_tile_3 = new HarvestTile(3, 3, 0, 1);
	HarvestTile* starter_tile_4 = new HarvestTile(2, 3, 2, 1);

	int x_offset = 0;
	int y_offset = 0;

	if (numOfPlayers < 4) {
		x_offset = 2;
	}

	if (numOfPlayers < 3) {
		x_offset = 2;
		y_offset = 2;
	}

	gameBoard->PlaceTile(starter_tile_1, (2 - x_offset), (2 - y_offset));
	gameBoard->PlaceTile(starter_tile_2, (10 - x_offset), (2 - y_offset));
	gameBoard->PlaceTile(starter_tile_3, (2 - x_offset), (10 - y_offset));
	gameBoard->PlaceTile(starter_tile_4, (10 - x_offset), (10 - y_offset));


	//Generate the remaining number of tiles before we start.
	if (numOfPlayers == 4)
		remainingTiles = 41;
	if (numOfPlayers == 3)
		remainingTiles = 31;
	if (numOfPlayers == 2)
		remainingTiles = 21;

	if (numOfPlayers < 2 || numOfPlayers > 4)
		remainingTiles = 1;


	harvest_deck = HarvestDeck();
	cout << "A harvest deck has been created with " << harvest_deck.GetCardCount() << " cards." << endl;
	building_deck = BuildingDeck();
	cout << "A building deck has been created with " << building_deck.GetCardCount() << " cards." << endl;

	for (int i = 0; i < gameBoard->buildings->size(); i++) {
		gameBoard->buildings->at(i) = building_deck.DrawBuildingTile();
	}

	string player_name;
	int player_id;
	int counter = 0;

	while (counter < numOfPlayers) {
		cout << "***********************************************************" << endl;
		cout << "Enter the name of Player " << (counter + 1) << ": ";
		cin >> player_name;
		cout << "Enter the id of Player " << (counter + 1) << ": ";
		cin >> player_id;
		players[counter] = new Player(player_name, player_id, harvest_deck, building_deck);
		//Stratford, Guilford, Fairfield, Milford.
		if (counter == 0) {
			players[counter]->player_board->setName("Stratford");
		}
		if (counter == 1) {
			players[counter]->player_board->setName("Guilford");
		}
		if (counter == 2) {
			players[counter]->player_board->setName("Fairfield");
		}
		if (counter == 3) {
			players[counter]->player_board->setName("Milford");
		}

		counter++;
	}
}

int findFirstPlayer() {
	Player* min = players[0];
	int minIndex = 0;
	for (int i = 0; i < numOfPlayers; i++) {
		if (*(players[i]->id) < *(min->id)) {
			min = players[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void drawVillage(int turn) {
	cout << endl;
	cout << "*********************************************************" << endl;
	cout << "**" << *(players[turn]->name) << "**" << endl;
	int drawCounter = 0;
	gameBoard->PrintResources();

	//checks how many resources are at 0 to see how many new village tiles may be drawn
	if (*(gameBoard->RMWood) == 0)
		drawCounter++;
	if (*(gameBoard->RMStone) == 0)
		drawCounter++;
	if (*(gameBoard->RMSheep) == 0)
		drawCounter++;
	if (*(gameBoard->RMGrain) == 0)
		drawCounter++;

	bool empty[6] = { false, false, false, false, false, false };
	bool invalidResponse = true;
	for (int i = 0; i < drawCounter; i++) {
		do {
			invalidResponse = true;

			cout << endl;
			cout << "The village tiles present on the board are: " << endl;
			gameBoard->printVillageTiles();
			cout << endl;
			cout << "The Village tiles you have in hand are:" << endl;
			players[turn]->PrintBuildingHand();
			cout << endl;
			cout << "remaining draws " << (drawCounter - i) << endl;
			cout << "**" << *(players[turn]->name) << "** enter the number of which building you wish to draw or d to draw from the deck (1-6 or d)";
			string response;
			cin >> response;

			if (response.length() == 1) {
				if (std::all_of(response.begin(), response.end(), ::isdigit)) {
					int x = stoi(response);
					if (x > 0 && x < 7) {
						if (!empty[x - 1]) { //if that spot on the board is not empty
							players[turn]->building_hand->push_back(gameBoard->buildings->at(x - 1));
							gameBoard->buildings->at(x - 1) = NULL;
							empty[x - 1] = true;
							invalidResponse = false;
						}
						else {
							cout << "that building spot is empty" << endl;
						}
					}
					else {
						cout << "invalid index" << endl;
					}
				}
				else if (response.compare("d") == 0 && i != 0) { //if player chooses to draw from deck if not on first draw
					players[turn]->DrawBuilding(1, building_deck);
					invalidResponse = false;
				}
				else {
					cout << "the first village drawn must be from the board" << endl;
				}
			}
			else {
				cout << "invalid entry" << endl;
			}
		} while (invalidResponse);
	}

	for (int i = 0; i < 6; i++) { //refill any empty building spots on map
		if (empty[i] == true) {
			gameBoard->buildings->at(i) = building_deck.DrawBuildingTile();;
		}
	}
	cout << endl;
	cout << "**" << *(players[turn]->name) << "** your village hand currently looks like:" << endl;
	players[turn]->PrintBuildingHand();
}

void promptHarvestTilePlacement(int turnIndex) {
	string input;
	bool validInput = false;
	int harvestTileIndex;
	int x;
	int y;

	do {
		// player will answer in format HARVEST_TILE_NUM X,Y
		// e.g. 2 0 0 to place the 2nd tile in the player's hand onto (0,0).
		cout << "Which harvest tile would **" << *players[turnIndex]->name << "** like to place and where? or H for Help): ";
		std::getline(std::cin >> std::ws, input);
		cout << "You inputted " << input << endl;

		// ---------------------------------------------------
		// HELP (PLAYER REQUIRES EXAMPLES OF VALID INPUTS)
		// ---------------------------------------------------
		if (input == "H" || input == "h") {
			cout << "A valid input would look like \"1 0 5\", where 1 = the first tile in your hand, 0 = x-axis and 5 = y-axis. "
				"The first resource will be placed on the specified x,y axis, while the remaining 3 resources will be placed on the right, bottom-right, and bottom respectively "
				"(i.e. the x,y coordinate inputted will be the top-left corner of the tile)." << endl;
			cout << "Please ensure that the input is exact (make sure there is one space between each digit, with no commas, tabs, etc) "
				"and that the coordinates you have selected on the Game Board are valid, i.e. is currently empty and (x&y)modulo(2) = 0." << endl;
			continue;
		}

		// ---------------------------------------------------
		// BEGIN INPUT VALIDATION (PLAYER ATTEMPTS TO BUILD)
		// ---------------------------------------------------

		// 1) validate 3 separate inputs (indicated by 2 spaces)
		if (std::count(input.begin(), input.end(), ' ') == 2) {
			string harvestTileIndexStr = input.substr(0, input.find(" "));
			string xStr = input.substr(harvestTileIndexStr.size() + 1, input.substr(harvestTileIndexStr.size() + 1).find(" "));
			string yStr = input.substr(harvestTileIndexStr.size() + xStr.size() + 2);

			// 2) validate the 2nd input (x coordinate) is a digit
			if (std::all_of(xStr.begin(), xStr.end(), ::isdigit)) {
				x = std::stoi(xStr);
				// 3) validate the x coordinate chosen fits in range
				if (x < gameBoard->pgbA->size()) {
					// 4) validate the 3rd input (y coordinate) is a digit
					if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
						y = std::stoi(yStr);
						// 5) validate the y coordinate chosen fits in range
						if (y < gameBoard->pgbA->at(0).size()) {
							// 6) validate first input (harvest tile index) is a digit
							if (std::all_of(harvestTileIndexStr.begin(), harvestTileIndexStr.end(), ::isdigit)) {
								harvestTileIndex = std::stoi(harvestTileIndexStr);
								// 7) validate the number chosen fits in range
								if (harvestTileIndex > 0 && harvestTileIndex <= players[turnIndex]->harvest_hand->size()) {
									harvestTileIndex--;
									// ---------------------------------------------------
									// DONE INPUT CHECK
									// ---------------------------------------------------

									// 8) prompt player if they wish to rotate the Harvest Tile before placing
									bool done = false;
									string doneInput;
									do {
										players[turnIndex]->harvest_hand->at(harvestTileIndex)->PrintHarvestTile();
										std::cout << "Type L to rotate this tile Left, or R to rotate Right (or D if done rotating): ";
										std::cin >> doneInput;
										std::cout << endl;
										if (doneInput == "L" || doneInput == "l")
											players[turnIndex]->harvest_hand->at(harvestTileIndex)->RotateTileLeft();
										else if (doneInput == "R" || doneInput == "r")
											players[turnIndex]->harvest_hand->at(harvestTileIndex)->RotateTileRight();
										else if (doneInput == "D" || doneInput == "d")
											done = true;
										else
											cout << "Sorry, I didn't quite get that!" << endl;

									} while (!done);

									// ---------------------------------------------------
									// PLACE THE TILE
									// ---------------------------------------------------
									validInput = players[turnIndex]->PlaceHarvestTile(gameBoard, harvestTileIndex, x, y);
								}
								// ---------------------------------------------------
								// SHIPMENT TILE PROMPT
								// ---------------------------------------------------
								else if (harvestTileIndex == players[turnIndex]->harvest_hand->size() + 1) {

									int resourceTypeIndex;
									string resourceTypeInput;
									bool validResourceTypeInput = false;

									do {
										cout << "1) WOOD" << endl;
										cout << "2) GRAIN" << endl;
										cout << "3) SHEEP" << endl;
										cout << "4) STONE" << endl;
										cout << "Please pick a resource type to fill your shipment tile with [1-4]: ";
										cin >> resourceTypeInput;
										cout << endl;

										// validate resource type input is simply 1-4
										if (resourceTypeInput.size() == 1) {
											if (std::all_of(resourceTypeInput.begin(), resourceTypeInput.end(), ::isdigit)) {
												int resourceTypeIndex = std::stoi(resourceTypeInput);
												if (resourceTypeIndex > 0 && resourceTypeIndex < 5) {
													validResourceTypeInput = true; 
													validInput = players[turnIndex]->PlaceShipmentTile(gameBoard, resourceTypeIndex - 1, x, y);
												}
											}
										}

										if (!validResourceTypeInput)
											cout << "Sorry! I didn't quite get that." << endl;

									} while (!validResourceTypeInput);
								}
							}
						}
					}
				}
			}
		}

		if (!validInput)
			cout << "Please enter a valid input." << endl;

	} while (!validInput);
};

void promptBuildingTilePlacement(int turnIndex) {
	string input;
	string flippedInput;
	bool validInput = false;
	bool validFlippedInput = false;
	int buildingTileIndex;
	int x;
	int y;
	bool flipped;

	do {
		// player will answer in format {HARVEST_TILE_NUM X Y}
		// e.g. 2 0 0 to place the 2nd tile in the player's hand onto (0,0).
		cout << endl;
		cout << "Which building tile would " << *players[turnIndex]->name << " like to place and where? (or type Q to Quit or H for Help): ";
		std::getline(std::cin >> std::ws, input);
		cout << "You inputted " << input << endl;

		// ---------------------------------------------------
		// QUIT (PLAYER CANNOT BUILD OR CHANGES THEIR MIND)
		// ---------------------------------------------------
		if (input == "Q" || input == "q")
			break;

		// ---------------------------------------------------
		// HELP (PLAYER REQUIRES EXAMPLES OF VALID INPUTS)
		// ---------------------------------------------------
		if (input == "H" || input == "h") {
			cout << "A valid input would look like \"1 0 2\", where 1 = the first tile in your hand, 0 = x-axis and 2 = y-axis." << endl;
			cout << "Please ensure that the input is exact (make sure there is one space between each digit, with no commas, tabs, etc) "
				"and that the coordinates you have selected on your board are valid, i.e. is currently an empty tile, "
				"is in an appropriate row for the tile being placed and would not cost more resources than available. "
				"You will later be prompted if you'd like the tile to be facedown or not, so do not worry about that yet." << endl;
			continue;
		}

		// ---------------------------------------------------
		// BEGIN INPUT VALIDATION (PLAYER ATTEMPTS TO BUILD)
		// ---------------------------------------------------

		// 1) validate 3 separate inputs (indicated by 2 spaces)
		if (std::count(input.begin(), input.end(), ' ') == 2) {
			string buildingTileIndexStr = input.substr(0, input.find(" "));
			string xStr = input.substr(buildingTileIndexStr.size() + 1, input.substr(buildingTileIndexStr.size() + 1).find(" "));
			string yStr = input.substr(buildingTileIndexStr.size() + xStr.size() + 2);

			// 2) validate first input (harvest tile index) is a digit
			if (std::all_of(buildingTileIndexStr.begin(), buildingTileIndexStr.end(), ::isdigit)) {
				buildingTileIndex = std::stoi(buildingTileIndexStr);

				// 3) validate the number chosen fits in range
				if (buildingTileIndex > 0 && buildingTileIndex <= players[turnIndex]->building_hand->size()) {
					buildingTileIndex--;

					// 4) validate the 2nd input (x coordinate) is a digit
					if (std::all_of(xStr.begin(), xStr.end(), ::isdigit)) {
						x = std::stoi(xStr);

						// 5) validate the x coordinate chosen fits in range
						if (x < players[turnIndex]->player_board->map->size()) {

							// 6) validate the 3rd input (y coordinate) is a digit
							if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
								y = std::stoi(yStr);

								// 7) validate the y coordinate chosen fits in range
								if (y < players[turnIndex]->player_board->map->at(0).size()) {
									// ---------------------------------------------------
									// DONE INPUT CHECK
									// ---------------------------------------------------

									// 8) prompt player if they want the tile to be flipped
									do {
										cout << "Do you want to place the tile facedown? [Y/N]: ";
										std::getline(std::cin >> std::ws, flippedInput);

										// validate flipped input is a simple yes/no
										if (flippedInput == "Y" || flippedInput == "y") {
											flipped = true;
											validFlippedInput = true;
										}
										else if (flippedInput == "N" || flippedInput == "n") {
											flipped = false;
											validFlippedInput = true;
										}
										else {
											cout << "Sorry! I didn't quite get that." << endl;
										}

									} while (!validFlippedInput);

									// 9) validate sufficient resources
									if (validateSufficentResources(x, y, turnIndex, buildingTileIndex, flipped)) {
										// 10) determine num of resources to be deducted, which will be passed to deductResources() if the tile placement is successful.
										//     this must be remembered here, because the tile in hand is erased immediately after placed onto the board.
										int numResourcesToDeduct;
										building_type resourceToDeduct = *players[turnIndex]->building_hand->at(buildingTileIndex)->bt_ptr;
										if (flipped)
											numResourcesToDeduct = *players[turnIndex]->building_hand->at(buildingTileIndex)->bv_ptr;
										else
											numResourcesToDeduct = (*players[turnIndex]->player_board->height - y);

										// 11) build the village
										validInput = players[turnIndex]->BuildVillage(x, y, buildingTileIndex, flipped);

										// 12) if successful, deduct reasources spent
										if (validInput) {
											deductResources(resourceToDeduct, numResourcesToDeduct);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if (!validInput)
			cout << "Please enter a valid input, or enter H (Help) for examples of a valid input." << endl;
	} while (!validInput);

};

bool validateSufficentResources(int x, int y, int turnIndex, int buildingTileIndex, bool flipped) {
	// check if remaining resources on board are greather than or equal to the value of the Building Tile (or, if flipped, the value of the row)
	switch (*players[turnIndex]->building_hand->at(buildingTileIndex)->bt_ptr) {
	case GRAIN:
		if ((!flipped && *gameBoard->RMGrain >= *players[turnIndex]->building_hand->at(buildingTileIndex)->bv_ptr)
			|| (flipped && *gameBoard->RMGrain >= *players[turnIndex]->player_board->height - y)) {
			return true;
		}
		else {
			cout << "Sorry, you don't have enough grain to build that!" << endl;
			return false;
		}
		break;
	case WOOD:
		if ((!flipped && *gameBoard->RMWood >= *players[turnIndex]->building_hand->at(buildingTileIndex)->bv_ptr)
			|| (flipped && *gameBoard->RMWood >= *players[turnIndex]->player_board->height - y)) {
			return true;
		}
		else {
			cout << "Sorry, you don't have enough wood to build that!" << endl;
			return false;
		}
		break;
	case SHEEP:
		if ((!flipped && *gameBoard->RMSheep >= *players[turnIndex]->building_hand->at(buildingTileIndex)->bv_ptr)
			|| (flipped && *gameBoard->RMSheep >= *players[turnIndex]->player_board->height - y)) {
			return true;
		}
		else {
			cout << "Sorry, you don't have enough sheep to build that!" << endl;
			return false;
		}
		break;
	case STONE:
		if ((!flipped && *gameBoard->RMStone >= *players[turnIndex]->building_hand->at(buildingTileIndex)->bv_ptr)
			|| (flipped && *gameBoard->RMStone >= *players[turnIndex]->player_board->height - y)) {
			return true;
		}
		else {
			cout << "Sorry, you don't have enough stone to build that!" << endl;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

void deductResources(building_type bt_ptr, int numResourcesToDeduct) {
	// deducts resources of board by the value on Building Tile (or, if flipped, by the value of the row) 
	switch (bt_ptr) {
	case WHEATFIELD:
		*gameBoard->RMGrain = *gameBoard->RMGrain - numResourcesToDeduct;
		break;
	case FOREST:
		*gameBoard->RMWood = *gameBoard->RMWood - numResourcesToDeduct;
		break;
	case MEADOW:
		*gameBoard->RMSheep = *gameBoard->RMSheep - numResourcesToDeduct;
		break;
	case QUARRY:
		*gameBoard->RMStone = *gameBoard->RMStone - numResourcesToDeduct;
		break;
	}
}

void computeGameScore() {
	vector<Player*> player_list;
	for (size_t i = 0; i < numOfPlayers; i++) {
		player_list.push_back(players[i]);
	}

	int hiscore = 0; //find player with highest score and store any player with same score in a vector, can probably have this as a method tha return a vector of *Players and accept a vector of *Players to avoid redundancy
	vector<int> player_scores;

	for (size_t i = 0; i < player_list.size(); i++) {
		int score = (*(player_list)[i]->player_board).calculateScore();
		player_scores.push_back(score);
		if (score > hiscore) {
			hiscore = score;
		}
	}

	vector<Player*> hiscore_player_list;
	for (size_t i = 0; i < player_scores.size(); i++) {
		if (hiscore == player_scores[i]) {
			hiscore_player_list.push_back(player_list[i]);
		}
	}

	if (hiscore_player_list.size() > 1) {

		int most_filled = 0; //find player with the most filled village and store any player with same placed buildingTile number in a vector
		vector<int> player_VGtiles;

		for (size_t i = 0; i < hiscore_player_list.size(); i++) {
			int filled_tiles = 0;
			VGMap& temp_village_board = *(players[i]->player_board);
			for (size_t j = 0; j < temp_village_board.map->size(); j++) {
				for (size_t k = 0; k < (*temp_village_board.map)[0].size(); k++) {
					if (*((*temp_village_board.map)[j][k]->bt_ptr) != NO_BUILDING) {
						filled_tiles++;
					}
				}
			}
			player_VGtiles.push_back(filled_tiles);
			if (filled_tiles > most_filled) {
				most_filled = filled_tiles;
			}
		}

		vector<Player*> most_village_players;
		for (size_t i = 0; i < player_VGtiles.size(); i++) {
			if (player_VGtiles[i] == most_filled) {
				most_village_players.push_back(hiscore_player_list[i]);
			}
		}

		if (most_village_players.size() > 1) {

			int least_VGhand = most_village_players[0]->building_hand->size(); // find player with least buildingTiles on hand, store any player with equal number of buildingTiles in a vector

			vector<int> player_VGhand;
			for (size_t i = 0; i < most_village_players.size(); i++) {
				int VGhand_size = most_village_players[i]->building_hand->size();
				player_VGhand.push_back(VGhand_size);
				if (VGhand_size < least_VGhand) {
					least_VGhand = VGhand_size;
				}
			}

			vector<Player*> least_VGhand_players;
			for (size_t i = 0; i < player_VGhand.size(); i++) {
				if (player_VGhand[i] == least_VGhand) {
					least_VGhand_players.push_back(most_village_players[i]);
				}
			}

			displayWinner(least_VGhand_players);//print winner with least village on hands
			return;
		}

		displayWinner(most_village_players);//print winner with most filled village
		return;
	}

	displayWinner(hiscore_player_list);	//prrint winner with highest score
	return;
}

void displayWinner(vector<Player*> winners) {
	cout << "\nGame finished:\n";
	for (Player* winner : winners) {
		cout << "Winner: " << *(winner->name) << " Score: " << (*winner->player_board).calculateScore() << endl;
	}
	return;
}
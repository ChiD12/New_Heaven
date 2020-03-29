#include "GameDriver.h"
#include <limits.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	gameStart();
	bool gameEnd = false;
	remainingTiles = 45; //Use this for testing for now.

	int turnCounter = findFirstPlayer();

	while (!gameEnd) {
		int turn = turnCounter % numOfPlayers;
		cout << "It is " << *(players[turn]->name) << "'s turn" << endl;

		cout<<"current score: " << (*(players)[turn]->player_board).calculateScore()<< endl;//testing
		
		cout << "The current Board State is: " << endl;
		gameBoard->PrintBoard();
		cout << "You currently are holding these Harvest Tiles: " << endl;
		players[turn]->PrintHarvestHand();

		promptHarvestTilePlacement(turn);
		
		

		cout << "and " << *(players[turn]->name) << "'s village board is: " << endl;
		players[turn]->player_board->PrintVillageBoard();

		turnCounter++;
		if (remainingTiles < 1) {
			gameEnd = true;
		}
	}
}


void gameStart()
{
	cout << "Starting game!" << endl;

	cout << "How many people will be playing today?: ";

	cin >> numOfPlayers;

	cout << "Great! You've chosen to play with " << numOfPlayers << " players." << endl;

	gameBoard = new GBMap(numOfPlayers);

	gameBoard->PrintBoard();

	gameBoard->PrintResources();

	harvest_deck = HarvestDeck();
	building_deck = BuildingDeck();

	string player_name;
	int player_id;
	int counter = 0;

	while (counter < numOfPlayers) {
		cout << "Enter the name of Player " << (counter + 1) << ": ";
		cin >> player_name;
		cout << "Enter the id of Player " << (counter + 1) << ": ";
		cin >> player_id;
		players[counter] = new Player(player_name, player_id, harvest_deck, building_deck);

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

void promptHarvestTilePlacement(int index) {
	//players[index]->PrintHarvestHand();
	//gameBoard->PrintBoard();

	string input;
	bool validInput = false;
	int harvestTileIndex;
	int x;
	int y;

	do {
		// player will answer in format HARVEST_TILE_NUM X,Y
		// e.g. 2 0 0 to place the 2nd tile in the player's hand onto (0,0).
		cout << "Which harvest tile would " << *players[index]->name << " like to place and where?: ";
		std::getline(std::cin >> std::ws, input);
		cout << "You inputted " << input << endl;

		// 1) validate 3 separate inputs (indicated by 2 spaces)
		if (std::count(input.begin(), input.end(), ' ') == 2) {
			string harvestTileIndexStr = input.substr(0, input.find(" "));
			string xStr = input.substr(harvestTileIndexStr.size() + 1, input.find(" "));
			string yStr = input.substr(harvestTileIndexStr.size() + xStr.size() + 2);

			// 2) validate first input (harvest tile index) is a digit
			if (std::all_of(harvestTileIndexStr.begin(), harvestTileIndexStr.end(), ::isdigit)) {
				harvestTileIndex = std::stoi(harvestTileIndexStr);
				// 3) validate the number chosen fits in range
				if (harvestTileIndex <= players[index]->harvest_hand->size()) {
					// 4) validate the 2nd input (x coordinate) is a digit
					if (std::all_of(xStr.begin(), xStr.end(), ::isdigit)) {
						x = std::stoi(xStr);
						// 5) validate the x coordinate chosen fits in range
						if (x < gameBoard->pgbA->at(0).size()) {
							// 6) validate the 3rd input (y coordinate) is a digit
							if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
								y = std::stoi(yStr);
								// 7) validate the y coordinate chosen fits in range
								if (y < gameBoard->pgbA->size()) {
									// DONE!
									validInput = players[index]->PlaceHarvestTile(gameBoard, players[index]->harvest_hand->at(harvestTileIndex-1), x, y);
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

	// TODO: HARVEST TILE NEEDS TOSTRING
	//cout << "Placing " << *players[index]->harvest_hand->at(harvestTileIndex) << "onto " << x << "," << y << endl;
	
	gameBoard->PrintBoard();
};

void promptBuildingTilePlacement(int index) {
	players[index]->PrintBuildingHand();
	players[index]->player_board->PrintVillageBoard();
	gameBoard->PrintResources();

	string input;
	string flippedInput;
	bool validInput = false;
	bool validFlippedInput = false;
	int buildingTileIndex;
	int x;
	int y;
	bool flipped;

	do {
		// player will answer in format HARVEST_TILE_NUM X,Y
		// e.g. 2 0 0 to place the 2nd tile in the player's hand onto (0,0).
		cout << "Which building tile would " << *players[index]->name << " like to place and where?: ";
		std::getline(std::cin >> std::ws, input);
		cout << "You inputted " << input << endl;

		do {
			cout << "Do you want to place the tile facedown? [Y/N]: ";
			std::getline(std::cin >> std::ws, flippedInput);

			// 1) validate flipped input is a simple yes/no
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
			

		// 2) validate 3 separate inputs (indicated by 2 spaces)
		if (std::count(input.begin(), input.end(), ' ') == 2) {
			string buildingTileIndexStr = input.substr(0, input.find(" "));
			string xStr = input.substr(buildingTileIndexStr.size() + 1, input.find(" "));
			string yStr = input.substr(buildingTileIndexStr.size() + xStr.size() + 2);

			// 3) validate first input (harvest tile index) is a digit
			if (std::all_of(buildingTileIndexStr.begin(), buildingTileIndexStr.end(), ::isdigit)) {
				buildingTileIndex = std::stoi(buildingTileIndexStr);
				// 4) validate the number chosen fits in range
				if (buildingTileIndex <= players[index]->building_hand->size()) {
					// 5) validate the 2nd input (x coordinate) is a digit
					if (std::all_of(xStr.begin(), xStr.end(), ::isdigit)) {
						x = std::stoi(xStr);
						// 6) validate the x coordinate chosen fits in range
						if (x < players[index]->player_board->map->at(0).size()) {
							// 7) validate the 3rd input (y coordinate) is a digit
							if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
								y = std::stoi(yStr);
								// 8) validate the y coordinate chosen fits in range
								if (y < players[index]->player_board->map->size()) {
									// 9) validate sufficient resources
									switch (*players[index]->building_hand->at(buildingTileIndex - 1)->bt_ptr) {
									case GRAIN:
										if (*gameBoard->RMGrain >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr)
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
										break;
									case WOOD:
										if (*gameBoard->RMWood >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr)
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
										break;
									case SHEEP:
										if (*gameBoard->RMSheep >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr)
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
										break;
									case STONE:
										if (*gameBoard->RMStone >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr)
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
										break;
									}
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

	// TODO: HARVEST TILE NEEDS TOSTRING
	//cout << "Placing " << *players[index]->harvest_hand->at(harvestTileIndex) << "onto " << x << "," << y << endl;

	gameBoard->PrintBoard();
};

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

	if (hiscore_player_list.size()>1) {

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

		if (most_village_players.size() > 1 ) {
			
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
	for (Player* winner: winners) {
		cout << "Winner: "<<*(winner->name) << " Score: " << (*winner->player_board).calculateScore() << endl;
	}
	return;
}
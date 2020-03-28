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
		
		cout << endl;
		cout << "*************************************************************"<< endl;
		cout << "It is **" << *(players[turn]->name) << "'s** turn" << endl;

		
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
		

		//allow other players to use up rest of resources
		for (int i = 0; i < numOfPlayers; i++) {
			int clockwisePlayers = (turn + i) % numOfPlayers;
			cout << "**************************************************************" << endl;
			cout << "and **" << *(players[clockwisePlayers]->name) << "'s** village board is: " << endl;
			players[clockwisePlayers]->player_board->PrintVillageBoard();
			gameBoard->PrintResources();
			players[clockwisePlayers]->PrintBuildingHand();
			cout << endl;
			cout << "**"<< *(players[clockwisePlayers]->name) << "** do you wish to place a village tile with remaining resources? (y or n)";
			string response;
			cin >> response;
			while (response.compare("y") == 0) {
				promptBuildingTilePlacement(clockwisePlayers);
				
				players[clockwisePlayers]->player_board->PrintVillageBoard();
				gameBoard->PrintResources();
				players[clockwisePlayers]->PrintBuildingHand();

				cout <<  "**" <<*(players[clockwisePlayers]->name) << "** do you wish to place a village tile with remaining resources? (y or n)" << endl;
				cin >> response;
			}
		}

		drawVillage(turn);

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
	
}


void gameStart()
{
	cout << "Starting game!" << endl;

	cout << "How many people will be playing today?: ";

	cin >> numOfPlayers;

	cout << "Great! You've chosen to play with " << numOfPlayers << " players." << endl;

	gameBoard = new GBMap(numOfPlayers);
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
	if (*(gameBoard->RMWood) == 0)
		drawCounter++;
	if (*(gameBoard->RMStone) == 0)
		drawCounter++;
	if (*(gameBoard->RMSheep) == 0)
		drawCounter++;
	if (*(gameBoard->RMGrain) == 0)
		drawCounter++;

	bool empty[6] = { false, false, false, false, false, false};
	bool invalidResponse =true;
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
						if (!empty[x-1]) { //if that spot on the board is not empty
							players[turn]->building_hand->push_back(gameBoard->buildings->at(x - 1));
							gameBoard->buildings->at(x - 1) = NULL;
							empty[x-1] = true;
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
	cout << "**" <<  *(players[turn]->name) << "** your village hand currently looks like:" << endl;
	players[turn]->PrintBuildingHand();
}

void promptHarvestTilePlacement(int index) {;
	string input;
	bool validInput = false;
	int harvestTileIndex;
	int x;
	int y;

	do {
		// player will answer in format HARVEST_TILE_NUM X,Y
		// e.g. 2 0 0 to place the 2nd tile in the player's hand onto (0,0).
		cout << "Which harvest tile would **" << *players[index]->name << "** like to place and where?: ";
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
						if (x < gameBoard->pgbA->size()) {
							// 6) validate the 3rd input (y coordinate) is a digit
							if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
								y = std::stoi(yStr);
								// 7) validate the y coordinate chosen fits in range
								if (y < gameBoard->pgbA->at(0).size()) {
									// DONE!
									validInput = players[index]->PlaceHarvestTile(gameBoard, players[index]->harvest_hand->at(harvestTileIndex-1), x, y, (harvestTileIndex - 1));
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

void promptBuildingTilePlacement(int index) {
	/*cout << endl;
	players[index]->player_board->PrintVillageBoard();
	gameBoard->PrintResources();
	players[index]->PrintBuildingHand();
	cout << endl;*/

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
		cout << endl;
		cout << "Which building tile would " << *players[index]->name << " like to place and where? (or type Q to Quit): ";
		std::getline(std::cin >> std::ws, input);
		cout << "You inputted " << input << endl;

		if (input == "Q" || input == "q")
			break;

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
						if (x < players[index]->player_board->map->size()) {
							// 7) validate the 3rd input (y coordinate) is a digit
							if (std::all_of(yStr.begin(), yStr.end(), ::isdigit)) {
								y = std::stoi(yStr);
								// 8) validate the y coordinate chosen fits in range
								if (y < players[index]->player_board->map->at(0).size()) {
									// 9) validate sufficient resources
									switch (*players[index]->building_hand->at(buildingTileIndex - 1)->bt_ptr) {
									case GRAIN:
										if (*gameBoard->RMGrain >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr) {
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
											// deduct resources spent
											if (validInput){
												*gameBoard->RMGrain = *gameBoard->RMGrain - *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr;
												players[index]->building_hand->erase((players[index]->building_hand->begin()) + (buildingTileIndex - 1)); //remove tile that was played from hand	
											}
										}
										else
											cout << "Sorry, you don't have enough grain to build that!" << endl;
										break;
									case WOOD:
										if (*gameBoard->RMWood >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr) {
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));										// deduct resources spent
											// deduct resources spent
											if (validInput) {
												*gameBoard->RMWood = *gameBoard->RMWood - *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr;
												players[index]->building_hand->erase((players[index]->building_hand->begin()) + (buildingTileIndex - 1)); //remove tile that was played from hand	
											}
										}
										else
											cout << "Sorry, you don't have enough wood to build that!" << endl;
										break;
									case SHEEP:
										if (*gameBoard->RMSheep >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr) {
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
											// deduct resources spent
											if (validInput){
												*gameBoard->RMSheep = *gameBoard->RMSheep - *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr;
												players[index]->building_hand->erase((players[index]->building_hand->begin()) + (buildingTileIndex - 1)); //remove tile that was played from hand	
											}
										}
										else
											cout << "Sorry, you don't have enough sheep to build that!" << endl;
										break;
									case STONE:
										if (*gameBoard->RMStone >= *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr) {
											validInput = players[index]->BuildVillage(x, y, flipped, *players[index]->building_hand->at(buildingTileIndex - 1));
											// deduct resources spent
											if (validInput){
												*gameBoard->RMStone = *gameBoard->RMStone - *players[index]->building_hand->at(buildingTileIndex - 1)->bv_ptr;
												players[index]->building_hand->erase((players[index]->building_hand->begin()) + (buildingTileIndex - 1)); //remove tile that was played from hand	
											}
										}
										else
											cout << "Sorry, you don't have enough stone to build that!" << endl;
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

};

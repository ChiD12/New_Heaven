#include "GameDriver.h"
#include <limits.h>;
#include <iostream>
#include <string>

using namespace std;

int main() {

	gameStart();
	bool gameEnd = false;
	remainingTiles = 45; //Use this for testing for now.

	int turnCounter = findFirstPlayer();

	while (!gameEnd) {
		int turn = turnCounter % numOfPlayers;
		cout << "it is " << players[turn]->name << "'s turn" << endl;
		cout << "The current Board State is: " << endl;
		gbMap->PrintBoard();

		bool validInput = true;
		int x;
		int y;
		do {
			validInput = true;
			cout << "please enter the coordinates of the top left of the Tile you wish to select in the form X,Y" << endl;
			string playerChoice;
			cin >> playerChoice;
			if (playerChoice.size() < 3) {
				validInput = false;
				cout << "invalid input" << endl;
			}
			try {
				int splitIndex = playerChoice.find(',');
				x = stoi(playerChoice.substr(0, splitIndex));
				y = stoi(playerChoice.substr(splitIndex, playerChoice.size()));
			}
			catch (invalid_argument const& e) {
				validInput = false;
				cout << "invalid input" << endl;
			}
		} while (!validInput);



		cout << "and " << players[turn]->name << "'s village board is: " << endl;
		players[turn]->player_board->showMap();


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

	GBMap game_board = GBMap(numOfPlayers);

	game_board.PrintBoard();

	game_board.PrintResources();

	HarvestDeck harvest_deck = HarvestDeck();
	BuildingDeck building_deck = BuildingDeck();

	string player_name;
	int player_id;
	int counter = 0;


	while (counter <= numOfPlayers) {
		cout << "Enter the name of Player " << (counter + 1)<< ": ";
		cin >> player_name;
		cout << "Enter the id of Player " << (counter + 1) << ": ";
		cin >> player_id;
		players[counter] = new Player(player_name, player_id, harvest_deck, building_deck);
	}
}

int findFirstPlayer() {

	Player* min = players[0];
	int minIndex = 0;
	for (int i = 0; i < 4; i++) {
		if ((players[i]->id) < (min->id)) {
			min = players[i];
			minIndex = i;
		}
	}
	return 0;
}
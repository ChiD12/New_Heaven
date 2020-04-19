#include "GameState.h"


//GameState::GameState() {};

GameState :: ~GameState() {
	delete numOfPlayers;
	delete remainingTiles;
	delete currentTurn;
	
	for (int i = 0; i < 4; i++) {
		if (players[i] != NULL) {
			delete players[i];
		}
	}

	delete gameBoard;
	delete harvest_deck;
	delete building_deck;
	delete currentGameSection;

	numOfPlayers = NULL;
	remainingTiles = NULL;
	currentTurn = NULL;
	gameBoard = NULL;
	harvest_deck = NULL;
	building_deck = NULL;
	currentGameSection = NULL;

}

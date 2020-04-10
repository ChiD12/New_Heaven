#pragma once
#include <vector>
#include "Resources.h"
#include "Player.h"



class  GameState {
public:

	int* numOfPlayers = new int;
	int* remainingTiles = new int;
	Player* players[4];
	GBMap* gameBoard;
	HarvestDeck* harvest_deck;
	BuildingDeck* building_deck;


	GameState();


};
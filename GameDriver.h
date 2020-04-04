#pragma once
#include "Resources.h"
#include "GBMap.h"
#include "VGMap.h"
#include "Player.h"
#include <vector>
#include <string>

int numOfPlayers;
int remainingTiles;
Player* players[4];
GBMap* gameBoard;
HarvestDeck harvest_deck;
BuildingDeck building_deck;

void gameStart();
int findFirstPlayer();
void drawVillage(int turn);

/**
		Takes the index of the turn player and prompts the player to place a Harvest Tile on the Game Board. 
		Various input validations are made and if all are passed, Player.PlaceHarvestTile() is called.
*/
void promptHarvestTilePlacement(int index);

/**
		Takes the index of the turn player and prompts the player to place a Building Tile on the Game Board.
		Various input validations are made and if all are passed, Player.BuildVillage() is called and
		the resource tracker is updated. 
*/
void promptBuildingTilePlacement(int index);

void computeGameScore();

void displayWinner(vector<Player*>);
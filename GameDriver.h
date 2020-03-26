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
void promptHarvestTilePlacement(int index);
void promptBuildingTilePlacement(int index);
void computeGameScore();
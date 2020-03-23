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
GBMap* gbMap;

void gameStart();
int findFirstPlayer();
void turnSequence(int index);
void computeGameScore();
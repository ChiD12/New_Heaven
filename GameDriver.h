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
VGMap* vgMap;

void gameStart();
int findFirstPlayer();
void turnSequence();
void computeGameScore();
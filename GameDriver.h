#pragma once
#include "Resources.h"
#include "GBMap.h"
#include "VGMap.h"
#include "Player.h"
#include <vector>
#include <string>

int numOfPlayers;
Player* Players[4];
GBMap* gbMap;
VGMap* vgMap;

void gameStart();
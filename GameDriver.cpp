#include "GameDriver.h"
#include <limits.h>;

int main() {

	int turnCounter = 0;
	bool gameEnd = false;
	remainingTiles = 45; //Use this for testing for now.
	sortPlayers();

	while (!gameEnd) {
		int turn = turnCounter % 5;


		turnCounter++;
	}

}

void sortPlayers() {
	
	for (int i = 0; i < 4; i++) {
		Player* min = players[i];
		int minIndex = 0;
		for (int j = (i + 1); j < 4; j++) {
			if ((players[j]->id) < (min->id)) {
				min = players[j];
				minIndex = j;
			}
			Player* swap = players[i];
			players[i] = players[minIndex];
			players[minIndex] = swap;
		}
	}
}
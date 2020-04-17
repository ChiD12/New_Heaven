#include "GameObservers.h"
#include "GameState.h"

GameObservers::GameObservers() {
	this->observable = NULL;
}
GameObservers::GameObservers(GameState* observable) {
	this->observable = observable;
	this->observable->attach(this);
}
GameObservers::GameObservers(const GameObservers& other_observer) {
	this->observable = other_observer.observable;
	this->observable->attach(this);

}
GameObservers::~GameObservers() {
	this->observable->detach(this);
}

void GameObservers::Update() {
	//we might need multiple observer because on the slides, this only calls a single display function
	//we could possibly remove the method below, make this a base class, and extend from this with whatever subset of display function needed
}

void GameObservers::DisplayGameBoard() {}//part 1
void GameObservers::DisplayResourceMarker() {}//part 1&2
void GameObservers::DisplayPlayerHarvestDeck() {}//part 1
void GameObservers::DisplayPlayerBuildingDeck() {}//part 1
void GameObservers::DisplayPlayerVillage() {}//part 1
void GameObservers::DisplayPlayerScore() {} //part 2
void GameObservers::DisplayPlayerNumber() {} //part 2
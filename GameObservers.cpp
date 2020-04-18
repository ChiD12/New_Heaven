#include "GameObservers.h"

#include <iostream>

//game turns
using namespace std;

TurnObserver::TurnObserver() {
	this->observable = NULL;
}
TurnObserver::TurnObserver(GameState* observable) {
	this->observable = observable;
	this->observable->attach(this);
}
TurnObserver::TurnObserver(const TurnObserver& other_observer) {
	this->observable = other_observer.observable;
	this->observable->attach(this);

}
TurnObserver::~TurnObserver() {
	this->observable->detach(this);
}

void TurnObserver::Update() {
	//we might need multiple observer because on the slides, this only calls a single display function
	//we could possibly remove the method below, make this a base class, and extend from this with whatever subset of display function needed
	cout << "---------------------------------------------------------------" << endl;
	this->DisplayPlayer();
	this->DisplayGameBoard();
	cout << "---------------------------------------------------------------" << endl;

}

void TurnObserver::DisplayPlayer() {
	cout << "Active Player: " << "Player " << (*observable->currentTurn + 1) << "{" << *observable->players[*observable->currentTurn]->name << "} " << endl;
	observable->players[*observable->currentTurn]->PrintPlayer();

};

void TurnObserver::DisplayGameBoard() {
	observable->gameBoard->PrintBoard();
}

void TurnObserver::DisplayPlayerBuildingDeck() {}//part 1
void TurnObserver::DisplayPlayerVillage() {
	observable->players[*observable->currentTurn]->player_board->PrintVillageBoard();
}

//game statistics

GameStatisticsObserver::GameStatisticsObserver() {
	this->observable = NULL;
}
GameStatisticsObserver::GameStatisticsObserver(GameState* observable) {
	this->observable = observable;
	this->observable->attach(this);
}
GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver& other_observer) {
	this->observable = other_observer.observable;
	this->observable->attach(this);

}
GameStatisticsObserver::~GameStatisticsObserver() {
	this->observable->detach(this);
}

void GameStatisticsObserver::GameStatisticsObserver::Update() {}

void GameStatisticsObserver::DisplayResourceMarker() {
	observable->gameBoard->PrintResources();
}
void GameStatisticsObserver::DisplayPlayerScore() {} //part 2
void GameStatisticsObserver::DisplayPlayerNumber() {
	
} //part 2
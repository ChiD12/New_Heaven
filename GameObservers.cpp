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
	
	
	cout << "---------------------------------------------------------------" << endl;
	cout << "Turn Observer:" << endl;
	cout << "---------------------------------------------------------------" << endl;
	this->DisplayPlayer();
	this->DisplayCurrentAction();
	this->DisplayGameBoard();
	cout << "---------------------------------------------------------------" << endl;
	if (*observable->currentGameSection == PLACEVILLAGETILE) {
		cout << *observable->players[*observable->currentTurn]->name << "'s Village Board: " << endl;
		observable->players[*observable->currentTurn]->player_board->PrintVillageBoard();
	}
}

void TurnObserver::DisplayPlayer() {
	cout << "Active Player: " << "Player " << (*observable->currentTurn + 1) << " {" << *observable->players[*observable->currentTurn]->name << "} " << endl;
	observable->players[*observable->currentTurn]->PrintPlayer();

};

void TurnObserver::DisplayGameBoard() {
	observable->gameBoard->PrintBoard();
}

void TurnObserver::DisplayCurrentAction()
{
	cout << "Player is currently: ";

	switch (*observable->currentGameSection) {
	case PLACEHARVESTTILE:;
		cout << "Playing a harvest tile...";
		break;
	case PLACEVILLAGETILE:;
		cout << "Playing a village tile...";
		break;
	case SHARETHEWEALTH:
		cout << "Sharing the wealth...";
		break;
	case DRAWVILLAGETILE:;
		cout << "Drawing a village tile...";
		break;
	default:;
		cout << "Help! I don't know what they're doing!";
	}
	cout << endl;
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

void GameStatisticsObserver::GameStatisticsObserver::Update() {
	cout << "---------------------------------------------------------------" << endl;
	cout << "GameStats Observer:" << endl;
	cout << "---------------------------------------------------------------" << endl;
	this->DisplayPlayerStats();
	this->DisplayPlayerVillage();
	this->DisplayResourceMarker();
	cout << "---------------------------------------------------------------" << endl;
}

void GameStatisticsObserver::DisplayResourceMarker() {
	observable->gameBoard->PrintResources();
}

void GameStatisticsObserver::DisplayPlayerStats() {
	cout << "Player stats: {name:#:score}" << endl;

	for (Player* player : observable->players)
	{
		if (player != nullptr)
		cout << "{" << *player->name << " [" << *player->id << "] Score: "<< player->getScore() << "}" << endl;
	}
	
} 
void GameStatisticsObserver::DisplayPlayerVillage() {

	cout << "Village Boards: " << endl;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;

	cout << "    " << *observable->players[0]->name << "          ";

	for (int k = 1; k < *observable->numOfPlayers; k++) {
		cout << *observable->players[k]->name << "            ";
	}

	cout << endl;
	
	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < *observable->numOfPlayers; j++) {
			observable->players[j]->player_board->PrintNumRow(i);
		}
		cout << endl;
	}

	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
}
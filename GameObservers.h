#pragma once
#include "Observer.h"
#include "GameState.h"

class TurnObserver: public Observer{
	GameState* observable;
public:
	TurnObserver();
	TurnObserver(GameState*);
	TurnObserver(const TurnObserver&);
	~TurnObserver();
	void Update();
	//we might need multiple observer because on the slides, this only calls a single display method
	//could possibly remove the method below, make this a base class, and extend from this with whatever subset of display function needed
	void DisplayPlayer();
	void DisplayGameBoard();//part 1
	void DisplayResourceMarker();//part 1&2
	void DisplayPlayerBuildingDeck();//part 1
	void DisplayPlayerVillage();//part 1

};

class GameStatisticsObserver : public Observer {
	GameState* observable;
public:
	GameStatisticsObserver();
	GameStatisticsObserver(GameState*);
	GameStatisticsObserver(const GameStatisticsObserver&);
	~GameStatisticsObserver();
	void Update();

	void DisplayResourceMarker();//part 1&2
	void DisplayPlayerScore(); //part 2
	void DisplayPlayerNumber(); //part 2

};
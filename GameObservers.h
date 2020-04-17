#pragma once
#include "Observer.h"
#include "GameState.h"

class GameObservers: public Observer{
	GameState* observable;
public:
	GameObservers();
	GameObservers(GameState*);
	GameObservers(const GameObservers&);
	~GameObservers();
	void Update();
	//we might need multiple observer because on the slides, this only calls a single display method
	//could possibly remove the method below, make this a base class, and extend from this with whatever subset of display function needed
	void DisplayGameBoard();//part 1
	void DisplayResourceMarker();//part 1&2
	void DisplayPlayerHarvestDeck();//part 1
	void DisplayPlayerBuildingDeck();//part 1
	void DisplayPlayerVillage();//part 1
	void DisplayPlayerScore(); //part 2
	void DisplayPlayerNumber(); //part 2

};
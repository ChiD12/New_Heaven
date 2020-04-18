#pragma once
#include "GameState.h"
#include "Observer.h"

//class GameState;
class TurnObserver: public Observer{
	GameState* observable;
public:
	TurnObserver();
	TurnObserver(GameState* observable);
	TurnObserver(const TurnObserver& other_observer);
	~TurnObserver();
	void Update();
	void DisplayPlayer();
	void DisplayGameBoard();
	void DisplayCurrentAction();
	


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
	void DisplayPlayerVillage();
	void DisplayPlayerStats(); 

};
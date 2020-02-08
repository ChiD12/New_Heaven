#include <string>
#include "GBMap.cpp"
using namespace std;

class GBMapLoader {
private:
	GameBoard* gb;

public:
	GBMapLoader();

	GameBoard* getGameBoard();
	void loadMap(string filename);
};
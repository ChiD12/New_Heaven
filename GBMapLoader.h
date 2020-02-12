#include <string>
#include <vector>
#include "Node.cpp"
using namespace std;

class GBMapLoader {
private:
	// GameBoard* gb;
	vector<vector<Node*>> map;

public:
	GBMapLoader();

	//GameBoard* getGameBoard();
	vector<vector<Node*>> getMap();

	void loadMap(string filename);
};
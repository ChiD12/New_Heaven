#include <string>
#include "Resources.cpp"
using namespace std;

class GBMapLoader {
private:
	// GameBoard* gb;
	vector<vector<Node*>> map;

public:
	GBMapLoader();

	vector<vector<Node*>> getMap();

	void loadMap(string filename);
};
#include <string>
#include "Resources.h"
using namespace std;

class GBMapLoader {
private:
	// GameBoard* gb;
	vector<vector<Node*>> map;

public:
	GBMapLoader();
	~GBMapLoader();

	vector<vector<Node*>> getMap();

	void loadMap(string filename);
};
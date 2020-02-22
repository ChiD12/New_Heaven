#include <string>
#include <vector>
#include "Resources.h"
using namespace std;

class VGMapLoader {
private:
	// VillageBoard* vb;
	vector<vector<BuildingTile*>> map;

public:
	VGMapLoader();

	vector<vector<BuildingTile*>> getMap();

	void loadMap(string filename);
};
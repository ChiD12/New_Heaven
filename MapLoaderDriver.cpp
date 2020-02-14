#include "GBMapLoader.cpp"
using namespace std;

void main() {
	GBMapLoader *loader = new GBMapLoader();

	loader->loadMap("maps/twoPlayer.txt");
	vector<vector<Node*>*> map = loader->getMap();
	
	int count = 0;
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y]->size(); x++) {
			count++;
			cout << "(" + to_string(*map[x]->at(y)->x_index) + "," + to_string(*map[x]->at(y)->y_index) + ") ";
		}
		cout << "" << endl;
	}

	cout << count << endl;
}
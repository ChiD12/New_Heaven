#include <vector>
#include <string>
#include <iostream>
#include "GBMapLoader.cpp"
using namespace std;

void main() {
	GBMapLoader *loader = new GBMapLoader();

	loader->loadMap("maps/twoPlayer.txt");
	GameBoard* gb = loader->getGameBoard();
	
	int count = 0;
	for (size_t y = 0; y < gb->map.size(); y++)
	{
		for (size_t x = 0; x < gb->map[y].size(); x++) {
			count++;
			cout << "(" + to_string(*gb->map[x][y]->x_index) + "," + to_string(*gb->map[x][y]->y_index) + ") ";
		}
		cout << "" << endl;
	}

	cout << count << endl;
}
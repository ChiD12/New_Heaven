#include "GBMapLoader.cpp"
using namespace std;

void main() {
	GBMapLoader *loader = new GBMapLoader();

	loader->loadMap("maps/twoPlayer.txt");
	vector<vector<Node*>> map = loader->getMap();
	
	int count = 0;
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++) {
			if (map[x][y] != NULL) {
				count++;
				cout << "(" + to_string(*map[x][y]->x_index) + "," + to_string(*map[x][y]->y_index) + ") ";
			}
		}
		cout << "" << endl;
	}
	
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].size(); x++) {
			if (map[x][y] != NULL) {
				cout << "(" + to_string(*map[x][y]->x_index) + "," + to_string(*map[x][y]->y_index) + "): ";

				for (int z = 0; z < 4; z++)
					if (map[x][y]->edge_list[z] != NULL)
						cout << "(" + to_string(*map[x][y]->edge_list[z]->x_index) + "," + to_string(*map[x][y]->edge_list[z]->y_index) + ") ";
				cout << "" << endl;
			}
		}
	}
	

	cout << count << endl;
}
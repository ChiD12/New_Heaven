#include "GBMapLoader.h"
#include "iostream"
using namespace std;

int main() {
	GBMapLoader gbLoader = GBMapLoader();
	//VGMapLoader vgLoader = VGMapLoader();

	gbLoader.loadMap("fourPlayer.txt");
	vector<vector<Node*>> map = gbLoader.getMap();

	int count = 0;
	for (size_t y = 0; y < map[0].size(); y++)
	{
		for (size_t x = 0; x < map.size(); x++) {
			if (*map[x][y]->valid) {
				count++;
				cout << "(" + to_string(*map[x][y]->x_index) + "," + to_string(*map[x][y]->y_index) + ") ";
			}
			else
				cout << "(X,X) ";
		}
		cout << "" << endl;
	}

	for (size_t y = 0; y < map[0].size(); y++)
	{
		for (size_t x = 0; x < map.size(); x++) {
			if (*map[x][y]->valid) {
				cout << "(" + to_string(*map[x][y]->x_index) + "," + to_string(*map[x][y]->y_index) + "): ";

				for (int z = 0; z < 4; z++)
					if (*map[x][y]->edge_list[z]->valid)
						cout << "(" + to_string(*map[x][y]->edge_list[z]->x_index) + "," + to_string(*map[x][y]->edge_list[z]->y_index) + ") ";
					else
						cout << "(X,X) ";

				cout << "" << endl;
			}
		}
	}


	cout << count << endl;
}
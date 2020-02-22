#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "iostream"
using namespace std;

int main() {

	GBMapLoader gbLoader = GBMapLoader();
	gbLoader.loadMap("fourPlayer.txt");
	vector<vector<Node*>> gbMap = gbLoader.getMap();
	int count = 0;

	cout << "---------------------------------------" << endl;
	cout << "GAME BOARD:" << endl;
	cout << "---------------------------------------" << endl;
	for (size_t y = 0; y < gbMap[0].size(); y++)
	{
		for (size_t x = 0; x < gbMap.size(); x++) {
			if (*gbMap[x][y]->valid) {
				count++;
				cout << "(" + to_string(*gbMap[x][y]->x_index) + "," + to_string(*gbMap[x][y]->y_index) + ") ";
			}
			else
				cout << "(X,X) ";
		}
		cout << "" << endl;
	}

	cout << "" << endl;
	cout << "---------------------------------------" << endl;
	cout << "ADJACENT NODES:" << endl;
	cout << "---------------------------------------" << endl;

	for (size_t y = 0; y < gbMap[0].size(); y++)
	{
		for (size_t x = 0; x < gbMap.size(); x++) {
			if (*gbMap[x][y]->valid) {
				cout << "(" + to_string(*gbMap[x][y]->x_index) + "," + to_string(*gbMap[x][y]->y_index) + "): ";

				for (int z = 0; z < 4; z++)
					if (*gbMap[x][y]->edge_list[z]->valid)
						cout << "(" + to_string(*gbMap[x][y]->edge_list[z]->x_index) + "," + to_string(*gbMap[x][y]->edge_list[z]->y_index) + ") ";
					else
						cout << "(X,X) ";

				cout << "" << endl;
			}
		}
	}

	cout << "Game Board size: "  + to_string(count) << endl;
	cout << "" << endl;

	VGMapLoader vgLoader = VGMapLoader();
	vgLoader.loadMap("villageBoard.txt");
	vector<vector<BuildingTile*>> vgMap = vgLoader.getMap();
	count = 0;

	cout << "---------------------------------------" << endl;
	cout << "VILLAGE BOARD:" << endl;
	cout << "---------------------------------------" << endl;
	for (size_t y = 0; y < vgMap[0].size(); y++)
	{
		for (size_t x = 0; x < vgMap.size(); x++) {
			if (*vgMap[x][y]->valid) {
				count++;
				cout << "(" + to_string(*vgMap[x][y]->x_index) + "," + to_string(*vgMap[x][y]->y_index) + ") ";
			}
			else
				cout << "(X,X) ";
		}
		cout << "" << endl;
	}

	cout << "" << endl;
	cout << "---------------------------------------" << endl;
	cout << "ADJACENT TILES:" << endl;
	cout << "---------------------------------------" << endl;

	for (size_t y = 0; y < vgMap[0].size(); y++)
	{
		for (size_t x = 0; x < vgMap.size(); x++) {
			if (*vgMap[x][y]->valid) {
				cout << "(" + to_string(*vgMap[x][y]->x_index) + "," + to_string(*vgMap[x][y]->y_index) + "): ";

				for (int z = 0; z < 4; z++)
					if (*vgMap[x][y]->edge_list[z]->valid)
						cout << "(" + to_string(*vgMap[x][y]->edge_list[z]->x_index) + "," + to_string(*vgMap[x][y]->edge_list[z]->y_index) + ") ";
					else
						cout << "(X,X) ";

				cout << "" << endl;
			}
		}
	}

	cout << "Village Board size: " + to_string(count) << endl;
}
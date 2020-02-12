#include "GBMap.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	GameBoard* gb = new GameBoard(14, 14);
	//int count = 0;
	// for (size_t i = 0; i < gb->map.size(); i++)
	// {
	// 	for (size_t j = 0; j < gb->map[i].size(); j++) {
	// 		//gb->map[i][j] = new Node(count);
	//         //cout << gb->map[i][j]->count;
	//         //cout << " ";
	// 	}
	//     cout << endl;
	// }
	Node* current = gb->map[3][3];
	for (size_t i = 0; i < 13; i++) {

		cout << *(current->x_index) << "  " << *(current->y_index) << endl;
		//cout << (current->edge_list[2])<< endl;
		current = (current->edge_list[2]);

	}

}

void GameBoard::update_edge_all() {

	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			for (size_t k = 0; k < 4; k++) {
				if (map[i][j] != NULL) {  //if current node is not null 
					if (k == 0 && j != 0 && map[i][j - 1] != NULL) { //north
						map[i][j]->edge_list[k] = (map[i][j - 1]);
					}
					if (k == 1 && i != 13 && map[i + 1][j] != NULL) { //east
						map[i][j]->edge_list[k] = (map[i + 1][j]);
					}
					if (k == 2 && j != 0 && map[i][j + 1] != NULL) { //south
						map[i][j]->edge_list[k] = (map[i][j + 1]);
					}
					if (k == 3 && i != 13 && map[i - 1][j] != NULL) { //west
						map[i][j]->edge_list[k] = (map[i - 1][j]);
					}
				}
			}
		}
	}
}

GameBoard::GameBoard() {};
GameBoard::GameBoard(vector<vector<Node*>> map) {
	this->map = map;

	int count = 0;
	for (size_t i = 0; i < this->map.size(); i++)
	{
		for (size_t j = 0; j < this->map[i].size(); j++) {
			count++;
			cout << "(" + to_string(*map[i][j]->x_index) + "," + to_string(*map[i][j]->y_index) + ") ";
		}
		cout << "" << endl;
	}
};

GameBoard::GameBoard(const int x, const int y) {
	xSize = &x;
	ySize = &y;

	map = vector<vector<Node*>>((*xSize), vector<Node*>((*ySize)));

	int count = 0;
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {

			if (!((*xSize) == 14 && (*ySize) == 14 && (i == 0 && j == 0) || (i == 0 && j == 13) || (i == 13 && j == 0) || (i == 13 && j == 13))) {
				map[i][j] = new Node(i, j);
			}
		}
	}

	update_edge_all();

	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j] != NULL) {
				//cout << *(map[i][j]->y_index) << endl;
				//cout << "(x: "<<*(map[i][j]->x_index) <<" y: "<<*(map[i][j]->y_index)<<") ";
			}
		}//cout << endl;
	}
};
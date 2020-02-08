#include "GBMap.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Node::Node() {};
Node::Node(int* x, int* y) {
	x_index = x;
	y_index = y;
	type = EMPTY;
	edge_list = new Node[4]; // 0 is north, 1 is east, 2 is south, 3 is west
}

void Node::update_edge()
{
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

	cout << count << endl;
}
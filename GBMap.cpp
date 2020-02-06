#include "GBMap.hpp"
#include <vector>
#include <iostream>
using namespace std;

void main() {
	GameBoard* gb = new GameBoard(14, 14);
}


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
GameBoard::GameBoard(const int x, const int y) {
	this->x = &x;
	this->y = &y;

	gb = vector<vector<Node>>(*this->x, vector<Node>(*this->y));

	int count = 0;
	for (size_t i = 0; i < gb.size(); i++)
	{
		for (size_t j = 0; j < gb[i].size(); j++) {
			count++;
		}
	}

	cout << count << endl;
}
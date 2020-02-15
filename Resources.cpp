#include "Resources.h"
using namespace std;

Node::Node() {};
Node::Node(int x, int y) {
	x_index = new int(x);
	y_index = new int(y);
	type = EMPTY;
	edge_list = vector<Node*>(4); // 0 is north, 1 is east, 2 is south, 3 is west
}
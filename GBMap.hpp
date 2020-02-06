#include <vector>
using namespace std;

enum resource_type { WOOD, STONE, SHEEP, GRAIN, EMPTY };

class Node {
public:
	int* x_index;
	int* y_index;

	resource_type type;
	resource_type* p_type;

	Node* edge_list;
	Node();
	Node(int* x, int* y);

	void update_edge();
};

class GameBoard {
public:
	const int* x;
	const int* y;
	vector<vector<Node>> gb;

	GameBoard();
	GameBoard(const int x, const int y);
};
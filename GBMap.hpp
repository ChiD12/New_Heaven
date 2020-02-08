#include <vector>
using namespace std;

enum resource_type { WOOD, STONE, SHEEP, GRAIN, EMPTY };


class Node {
public:
	int* x_index;
	int* y_index;

	//bool* invalid = new bool(false);
	 
	int count =0;

	resource_type type;
	resource_type* p_type;

	vector<Node*> edge_list;
	Node();
	Node(int x, int y);
	Node(int c);

	
};

class GameBoard {
public:
	const int* xSize;
	const int* ySize;
	vector<vector<Node*>> gbA;

	void update_edge(int x, int y);
	void update_edge_all();

	GameBoard();
	GameBoard(const int x, const int y);
};
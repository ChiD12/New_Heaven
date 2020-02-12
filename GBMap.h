#include <vector>
#include <Node.cpp>
using namespace std;


class GameBoard {
public:
	vector<vector<Node*>> map;
	const int* xSize;
	const int* ySize;

	void update_edge(int x, int y);
	void update_edge_all();

	GameBoard();
	GameBoard(vector<vector<Node*>> map);
	GameBoard(const int x, const int y);
};
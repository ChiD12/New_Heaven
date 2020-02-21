#include <vector>
using namespace std;

enum resource_type { WOOD, GRAIN, SHEEP, STONE, NO_RESOURCE };
enum building_type { FOREST, WHEATFIELD, MEADOW, QUARRY, NO_BUILDING };

/*
class HarvestDeck {
private:
	int harvest_card_count;
	int* hcc_ptr = &harvest_card_count;

public:
	HarvestDeck();
	~HarvestDeck();

	HarvestTile DrawHarvestTile();

};

class HarvestTile {
private:
	resource_type upper_left;
	resource_type upper_right;
	resource_type bottom_left;
	resource_type bottom_right;

	resource_type* ul_ptr = &upper_left;
	resource_type* ur_ptr = &upper_right;
	resource_type* bl_ptr = &bottom_left;
	resource_type* br_ptr = &bottom_right;

public:
	HarvestTile();
	~HarvestTile();

	void RotateTileRight();
	void RotateTileLeft();

};




class BuildingDeck {
private:
	int building_card_count;
	int* bcc_ptr = &building_card_count;

public:
	BuildingDeck();
	~BuildingDeck();

	BuildingTile DrawBuildingTile(); //Do the same here as I did for the DrawHarvestTile() method.

};
*/

class BuildingTile {

public:
	building_type type;
	building_type* bt_ptr = &type;

	int building_value;
	int* bv_ptr = &building_value;
	int* x_index;
	int* y_index;
	bool* flipped;
	bool* valid;
	vector<BuildingTile*> edge_list;

	BuildingTile();
	BuildingTile(int x, int y, bool valid = 1);
	~BuildingTile();
};


class Node {
public:
	int* x_index;
	int* y_index;
	resource_type type;
	resource_type* p_type = &type;
	vector<Node*> edge_list;
	bool* valid;

	Node();
	Node(int x, int y, bool valid = 1);
};
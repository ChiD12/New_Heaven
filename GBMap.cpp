#include "GBMap.h"
#include <vector>
#include <iostream>
#include <queue>  
using namespace std;

void GBMap::update_edge_all() {

	//cout << (*pgbA)[0].size() << endl;
	for (size_t i = 0; i < (*pgbA).size(); i++) {
		for (size_t j = 0; j < (*pgbA)[i].size(); j++) {


			if (*(*pgbA)[i][j]->valid) {  //if current node is not null 
				for (size_t k = 0; k < 4; k++) {


					if (k == 0 && j != 0 && *(*pgbA).at(i).at(j - 1)->valid) {//north

						(*((*pgbA).at(i).at(j))->edge_list).at(k) = (*pgbA).at(i).at(j - 1);

					}

					if (k == 1 && i != 13 && *(*pgbA).at(i + 1).at(j)->valid) { //east

						(*((*pgbA).at(i).at(j))->edge_list).at(k) = (*pgbA).at(i + 1).at(j);

					}

					if (k == 2 && j != 13 && *(*pgbA).at(i).at(j + 1)->valid) { //south
						(*((*pgbA).at(i).at(j))->edge_list).at(k) = (*pgbA).at(i).at(j + 1);
					}
					if (k == 3 && i != 0 && *(*pgbA).at(i - 1).at(j)->valid) { //west
						(*(*pgbA).at(i).at(j)->edge_list).at(k) = (*pgbA).at(i - 1).at(j);
					}
				}
			}

		}
	}
}

//Given a top left index and a HarvestTile object place that tiles resources into nodes
//returns true of valid tile choice, returns false if not
bool GBMap::PlaceTile(HarvestTile* given_tile, int tlX, int tlY) {

	if (tlX % 2 == 0 && tlY % 2 == 0
		&& *((*(this->pgbA)).at(tlX).at(tlY))->valid 
		&& *((*(this->pgbA)).at(tlX).at(tlY))->rt_ptr == resource_type::NO_RESOURCE) { //makes sure placement is not between tiles and is not already occupied

		((*(this->pgbA)).at(tlX).at(tlY))->setResourceType(*given_tile->ul_ptr); //top left
		((*(this->pgbA)).at(tlX + 1).at(tlY))->setResourceType(*given_tile->ur_ptr); //top right
		((*(this->pgbA)).at(tlX).at(tlY + 1))->setResourceType(*given_tile->bl_ptr); //bot left
		((*(this->pgbA)).at(tlX + 1).at(tlY + 1))->setResourceType(*given_tile->br_ptr); //bot right
		return true;
	}
	else {
		cout << "Sorry, you can't do that! A tile must be placed in an even X,Y coordinate that is valid and not occupied!";
		return false;
	}
};

vector<int> GBMap::CalculateResources(int x, int y) {
	//assume index is of top left point a Tile
	Node TLNode = *(*this->pgbA)[x][y];
	Node TRNode = *(*this->pgbA)[x + 1][y];
	Node BLNode = *(*this->pgbA)[x][y + 1];
	Node BRNode = *(*this->pgbA)[x + 1][y + 1];

	Node nodeArray[4] = { TLNode, TRNode, BLNode, BRNode };
	resource_type rtArray[4] = { *(TLNode.rt_ptr),*(TRNode.rt_ptr), *(BLNode.rt_ptr), *(BRNode.rt_ptr) };

	vector<int>* resources = new vector<int>(4);
	//0 = WOOD, 1 = GRAIN, 2= SHEEP, 3 = STONE

	resource_type resourceType;
	Node firstNode;
	for (int i = 0; i < 4; i++) {
		int points = 0;
		queue<Node> queue;
		vector<Node> visited;
		resourceType = rtArray[i];
		firstNode = nodeArray[i];

		if (*(firstNode.rt_ptr) == NO_RESOURCE) {
			return vector<int>();
		}
		queue.push(firstNode);
		visited.push_back(firstNode);
		//BFS
		while (!queue.empty()) {
			Node current = queue.front();
			vector<Node*> currentEL = *current.edge_list;
			points++;
			queue.pop();

			for (int i = 0; i < currentEL.size(); i++) {
				bool found = false;
				if (*currentEL[i]->valid) {
					if (*currentEL[i]->rt_ptr == resourceType) {
						for (Node visit : visited) {
							if (visit.compare(*currentEL[i])) { //equals method
								found = true; //if this node is found in the visited list ignore it
								break;
							}
						}
						if (!found) {
							queue.push(*currentEL[i]);
							visited.push_back(*currentEL[i]);
						}
					}
				}
			}
		}
		if (resourceType == WOOD) {
			(*resources).at(0) = points;
			*RMWood = points;
		}
		if (resourceType == STONE) {
			(*resources).at(3) = points;
			*RMStone = points;
		}
		if (resourceType == SHEEP) {
			(*resources).at(2) = points;
			*RMSheep = points;
		}
		if (resourceType == GRAIN) {
			(*resources).at(1) = points;
			*RMGrain = points;
		}
	}
	return *resources;
}

void GBMap::PrintResources(){
	cout << "Available Wood: " << *RMWood << "| Available Stone: " << *RMStone << "| Available Sheep: " << *RMSheep << "| Available Grain: " << *RMGrain << endl;
}


GBMap::GBMap() {};
GBMap::GBMap(int numPlayers) {
	GBMapLoader loader;
	loader.loadMap(numPlayers);
	pgbA = new vector<vector<Node*>>;
	*pgbA = loader.getMap();
	RMWood = new int(0);
	RMStone = new int(0);
	RMSheep = new int(0);
	RMGrain = new int(0);
	cout << "Game Board created for " << numPlayers << " players." << endl;
	buildings = new vector<BuildingTile*>(6);

	
	//update_edge_all();
}


void GBMap::PrintBoard(){
	for (int j = 0; j < pgbA[0].size(); j++){
		for (int i = 0; i < pgbA->size(); i++){
			if (*(*this->pgbA)[i][j]->valid) { cout << *(*this->pgbA)[i][j]->resource_rep; }
			else cout << "[N]";
		}
		cout << endl;
	}
	PrintResources();
	printVillageTiles();
}

void GBMap::printVillageTiles() {
	cout << "Tiles On Board: ";
	for (int i = 0; i < buildings->size(); i++) {
		cout << (i + 1) << ":"; 
		if(buildings->at(i) != NULL)
			buildings->at(i)->PrintBuildingTile();
		else 
			cout << "[EMPTY]";
		cout << " ";
	}
	cout << endl;
}

GBMap::~GBMap() {
	//delete(xSize, ySize);

	// for (size_t i = 0; i < (*pgbA).size(); i++){
	//     for (size_t j = 0; j < (*pgbA)[i].size(); j++){
	//         delete (*pgbA).at(i).at(j);
	//         (*pgbA).at(i).at(j) = NULL;   
	//     }
	// }
	pgbA->clear();

}
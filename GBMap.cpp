#include "GBMap.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	GameBoard* gb = new GameBoard(14, 14);
    //int count = 0;
    // for (size_t i = 0; i < gb->gbA.size(); i++)
	// {
	// 	for (size_t j = 0; j < gb->gbA[i].size(); j++) {
	// 		//gb->gbA[i][j] = new Node(count);
    //         //cout << gb->gbA[i][j]->count;
    //         //cout << " ";
	// 	}
    //     cout << endl;
	// }
    Node* current = gb->gbA[3][3];
    for (size_t i = 0; i < 13; i++){
        
        cout << *(current->x_index) << "  "  << *(current->y_index) << endl;
        //cout << (current->edge_list[2])<< endl;
        current = (current->edge_list[2]);
        
    }
    
}


Node::Node() {};
Node::Node(int x, int y) {
	x_index = new int(x);
	y_index = new int(y);
	type = EMPTY;
    edge_list =vector<Node*>(4);
    //Node *arr[4];
	//edge_list = arr; // 0 is north, 1 is east, 2 is south, 3 is west
}
Node::Node(int c){
    count = c;
};

void GameBoard::update_edge_all(){

    for (size_t i = 0; i < gbA.size(); i++){
        for (size_t j = 0; j < gbA[i].size(); j++){
            for (size_t k = 0; k < 4; k++){
                if(gbA[i][j]!= NULL){  //if current node is not null 
                    if(k == 0 && j != 0 && gbA[i][j-1] != NULL){ //north
                        gbA[i][j]->edge_list[k] = (gbA[i][j-1]);
                    }
                    if(k == 1 && i != 13 && gbA[i+1][j] != NULL){ //east
                        gbA[i][j]->edge_list[k] = (gbA[i+1][j]);
                    }
                    if(k == 2 && j != 0 && gbA[i][j+1] != NULL){ //south
                        gbA[i][j]->edge_list[k] = (gbA[i][j+1]);
                    }
                    if(k == 3 && i != 13 && gbA[i-1][j] != NULL){ //west
                        gbA[i][j]->edge_list[k] = (gbA[i-1][j]);
                    }
                }
            }
        }
    }
}


GameBoard::GameBoard() {};
GameBoard::GameBoard(const int x, const int y) {
	xSize = &x;
	ySize = &y;

	gbA = vector<vector<Node*>>((*xSize), vector<Node*>((*ySize)));

	int count = 0;
	for (size_t i = 0; i < gbA.size(); i++){
		for (size_t j = 0; j < gbA[i].size(); j++){
            
			if(!((*xSize) == 14 && (*ySize) == 14 && (i == 0 && j == 0) || (i == 0 && j == 13) || (i == 13 && j == 0 ) || (i == 13 && j == 13))){
                gbA[i][j] = new Node(i,j);
            }
		}
	}
    update_edge_all();
    
    
    for (size_t i = 0; i < gbA.size(); i++){
		for (size_t j = 0; j < gbA[i].size(); j++){
                if(gbA[i][j] != NULL){
                    //cout << *(gbA[i][j]->y_index) << endl;
                    //cout << "(x: "<<*(gbA[i][j]->x_index) <<" y: "<<*(gbA[i][j]->y_index)<<") ";
                }
		}//cout << endl;
	}
};
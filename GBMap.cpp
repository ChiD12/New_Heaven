#include "GBMap.hpp"
#include <vector>
#include <iostream>
using namespace std;




void main(){
    GameBoard *gb = new GameBoard(14, 14);
}


class GameBoard{
    public:
        const int* x;
        const int* y;
        vector<vector<Node>> *gb;
    
    GameBoard(){}
    GameBoard(const int x,const int y){
        this->x = &x;
        this->y = &y;

        gb = new vector<vector<Node>>(*this->x, vector<Node>(*this->y));

        int count = 0;
        for (int i = 0; i < gb->size; i++)
        {
            for (int j = 0; j < gb[i].size; j++) {
                count++;
            }
        }

        cout << count;
        //new_node = array_name;
         
        
    }
};

class Node{
    public:
    int* x_index;
    int* y_index;
    
    enum resource_type {WOOD, STONE, SHEEP, GRAIN, EMPTY};
    
    resource_type type = EMPTY;
    resource_type*  p_type = &type;
    Node* edge_list = new Node[4]; // 0 is north, 1 is east, 2 is south, 3 is west
    
    Node(){}
    Node(int* x, int* y){
        x_index = x;
        y_index = y;
    }

    

    void update_edge(){
        
    }
};

class Tile{
    
};
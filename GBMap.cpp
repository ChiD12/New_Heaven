#include "GBMap.hpp"





void main(){
    GameBoard *gb = new GameBoard();
}


class GameBoard{
    public:
    int* fourPlayerX = new int(7);
    int* fourPlayerY = new int(7);

    int* threePlayerX = new int(5);
    int* fourPlayerY = new int(7);

    int* twoPlayerX = new int(5);
    int* twoPlayerY = new int(5);

    static const int column_l = 15;
    static const int row_l = 15;
    
    *pcolumn_l=&column_l;
    prow_l;

    
   
    //Node* new_node = new Node[column_l][row_l];
    Node* NA[column_l][row_l];
    
    GameBoard(){}
    GameBoard(int x, int y){
        for (int i = 0; i < gb.count; i++)
        {
            /* code */
        }

        column_l = &x;
        row_l = &y;
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
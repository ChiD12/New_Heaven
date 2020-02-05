enum resource_type {WOOD, STONE, SHEEP, GRAIN, EMPTY};

class Node{
    public: 
    int* x_index;
    int* y_index;

    resource_type type;
    resource_type*  p_type;

    Node* edge_list;
    Node();
    Node(int& x, int& y);

    void update_edge();
};

class GameBoard{
    public: 
    int* fourPlayerX;
    int* fourPlayerY;

    int * threePlayerX;
    int* fourPlayerY;

    int* twoPlayerX;
    int* twoPlayerY;

    const int column_l;
    const int row_l;

    static int const *pcolumn_l;
    static int const *prow_l;

    Node* gb;

    GameBoard();
};
/*======================================================================
Program Name: Building Tetriminos with Classes!
Programmer: Ben Bruser
Programe Date: 2/1/15
Description: Creates a class that contains the varies
tetriminos in the game tetris, creates a grid for them to move left, right,
up, down, and also rotates the tetrimino array either left or right.
=======================================================================*/

#ifndef TETRIS_TETRIMINO
#define TETRIS_TETRIMINO

const int TETRIMINO_GRID_SIZE = 4;

struct Location {
    int row;
    int col;
};

class Tetrimino {
private: 
    int grid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE]; //contains only zeros and ones 
    char color; 
    Location location;
public:
    // constructor
    // Initialize grid, color, and location
    // The ‘type’ parameter will determine which piece we initialize grid to
    Tetrimino(int type = 7); // valid type values are 0-6

    //---------------------------------------------
    //accessors
    char getColor(); // returns the color of the tetrimino object
    Location getLocation(); // return the location of the Tetrimino
    void getGrid(int gridOut[][TETRIMINO_GRID_SIZE]);  // return the grid of the Tetrimino 

    //---------------------------------------------
    //mutators
    void setLocation(Location newLocation); // modify location.row and location.col
    void setLocation(int row, int col); // modify location.row and location.col
    
    void rotateLeft();
    void rotateRight();
	void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    
    //---------------------------------------------
    //others
    void dataDump(); // print out the value of grid, color, and location
};
#endif
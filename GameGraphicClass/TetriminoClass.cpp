/*================================================================
Program Name: Building Tetriminos with Classes!
Programmer: Ben Bruser
Programe Date: 2/1/15
Description: Creates a class that contains the varies
tetriminos in the game tetris, creates a grid for them to move left, right,
up, down, and also rotates the tetrimino array either left or right.
==================================================================*/
#include "TetriminoClass.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

/*=============================================================================
Constructor	   
==============================================================================*/
Tetrimino::Tetrimino(int type)
{
	static bool firstTime = true;
	if(firstTime)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		firstTime = false;
	}

	// Generate a random number if type is invalid
	if(type < 0 || type > 6){
		type = rand() % 7;
	}

	//Initialize Tetriminos
	int iTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 0 , 0 , 0},
		{1 , 1 , 1 , 1},
		{0 , 0 , 0 , 0},
	};
	int jTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 1 , 0 , 0},
		{0 , 1 , 1 , 1},
		{0 , 0 , 0 , 0},
	};
	int lTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 0 , 1 , 0},
		{1 , 1 , 1 , 0},
		{0 , 0 , 0 , 0},
	};
	int oTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 1 , 1 , 0},
		{0 , 1 , 1 , 0},
		{0 , 0 , 0 , 0},
	};
	int sTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 0 , 1 , 1},
		{0 , 1 , 1 , 0},
		{0 , 0 , 0 , 0},
	};
	int tTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{0 , 1 , 0 , 0},
		{1 , 1 , 1 , 0},
		{0 , 0 , 0 , 0},
	};
	int zTetrimino[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE] =
	{
		{0 , 0 , 0 , 0},
		{1 , 1 , 0 , 0},
		{0 , 1 , 1 , 0},
		{0 , 0 , 0 , 0},
	};

	//Initialize location for all Tetriminos
	location.col = 2;
	location.row = -1;

	//Logical structure to assign color and copy the tetrimino into a new array
	switch(type)
	{
	case 0: 
		color = 't';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = iTetrimino[row][column];
			}
		}
		break;
	case 1:
		color = 'b';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = jTetrimino[row][column];
			}
		}
		break;
	case 2:
		color = 'o';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = lTetrimino[row][column];
			}
		}
		break;
	case 3:
		color = 'y';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = oTetrimino[row][column];
			}
		}
		break;
	case 4:
		color = 'g';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = sTetrimino[row][column];
			}
		}
		break;
	case 5:
		color = 'p';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = tTetrimino[row][column];
			}
		}
		break;
	case 6:
		color = 'r';
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int column = 0; column < TETRIMINO_GRID_SIZE; column++)
			{
				grid[row][column] = zTetrimino[row][column];
			}
		}
		break;
	default:
		break;
	}
}
/*=========================================================================
Accessors
==========================================================================*/

/*
Function Name: getColor
Description:   returns the color variable
Arguments:     none
Return:		   color
*/
char Tetrimino::getColor()
{
	return color;
}

/*
Function Name: getLocation
Description:   returns the location variable
Arguments:     none
Return:		   location
*/
Location Tetrimino::getLocation()
{
	return location;
}

/*
Function Name: getGrid
Description:   copys the grid into a new grid
Arguments:     gridOut (int 2d array)
Return:		   none ( passes grid by reference)
*/
void Tetrimino::getGrid(int gridOut[][TETRIMINO_GRID_SIZE])
{
	for (int row = 0; row < TETRIMINO_GRID_SIZE; row++)
	{
		for(int col = 0; col < TETRIMINO_GRID_SIZE; col++)
		{
			gridOut[row][col] = grid[row][col];
		}
	}
}

/*====================================================================
Mutators
=====================================================================*/

/*
Function Name: setLocation
Description:   sets the location of the Tetrimino
Arguments:    newLocation (struct Location)
Return:		  none
*/
void Tetrimino::setLocation(Location newLocation)
{
	location.row = newLocation.row;     
	location.col = newLocation.col;
}
/*
Function Name: setLocation
Description:   sets the location of the Tetrimino
Arguments:     row (int), col (int)
Return:		   none
*/
void Tetrimino::setLocation(int row, int col)
{
	location.row = row;
	location.col = col;
}

/*
Function Name: rotateLeft
Description:  Rotates the array left 90 degrees
Arguments:    none 
Return:		  none 
*/
void Tetrimino::rotateLeft()
{
	//Declare temporary array for storing the rotated array
	int rotateArray[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	//Loop structure that rotates the array 90 degrees to the left
	for (int row = 0; row < TETRIMINO_GRID_SIZE; row++)
	{
		for(int col = 0; col < TETRIMINO_GRID_SIZE; col++)
		{
			//rotates the array by performing a swap of the row and column section in the "copy" process
			rotateArray[row][col] = grid[col][3 - row];
		}
	}

	//Loop structure to copy data from the temporary rotated array into the main array
	for (int row = 0; row < TETRIMINO_GRID_SIZE; ++row)
	{
		for(int col = 0; col < TETRIMINO_GRID_SIZE; ++col)
		{
			grid[row][col] = rotateArray[row][col];
		}
	}
}
/*
Function Name: rotateRight
Description:   Rotates the grid 90 degrees to the right
Arguments:     none
Return:		   none
*/
void Tetrimino::rotateRight()
{
	//Declare temporary array for storing the rotated array
	int rotateArray[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	//Loop structure that rotates the main array 90 degrees to the right
	for (int row = 0; row < TETRIMINO_GRID_SIZE; row++)
	{
		for (int col = 0; col < TETRIMINO_GRID_SIZE; col++)
		{
			//rotates the array by performing a swap of the row and column section in the "copy" process
			rotateArray [col][TETRIMINO_GRID_SIZE-1-row] = grid[row][col];
		}
	}

	//Loop structure to copy data from the temporary rotated array into the main array
	for (int row = 0; row < TETRIMINO_GRID_SIZE; ++row)
	{
		for(int col = 0; col < TETRIMINO_GRID_SIZE; ++col)
		{
			grid[row][col] = rotateArray[row][col];
		}
	}
}

/*
Function Name: moveLeft
Description: displaces the location left by 1 on the grid
Arguments: none
Return: none
*/
void Tetrimino::moveLeft()
{
	location.col = location.col - 1;
}

/*
Function Name: moveRight
Description: displaces the location right by 1 on the grid 
Arguments: none
Return: none
*/
void Tetrimino::moveRight()
{
	location.col = location.col + 1;
}

/*
Function Name: moveDown
Description: displaces the location down by 1 on the grid
Arguments: none
Return: none
*/
void Tetrimino::moveDown()
{
	location.row = location.row + 1;
}

/*
Function Name: moveUp
Description: displaces the location up by 1 on the grid
Arguments: none
Return: none
*/
void Tetrimino::moveUp()
{
	location.row = location.row - 1;
}

/*=============================================================================
Others
=============================================================================*/

/*
Function Name: dataDump
Description: prints out the grid, location, and color of the specific tetrimino
Arguments: none
Return: none
*/
void Tetrimino::dataDump()
{
	// the outer for loop steps through each row in the times table
	for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
	{
		// the inner loop steps through each column in the present row
		for(int column = 0; column < 4; column++)
		{
			cout << grid[row][column] << " ";
		}
		// Print a new line at the end of each row
		cout << endl;
	}

	cout << "Color: " << color << endl;
	cout << "Location: " << location.row << ", " << location.col << endl;
}
/*
void main()
{
//Tests to see if the constructor works
Tetrimino myTetrimino;

myTetrimino.dataDump();

myTetrimino.rotateRight();

myTetrimino.dataDump();

myTetrimino.rotateLeft();

myTetrimino.dataDump();

myTetrimino.moveLeft();

myTetrimino.dataDump();

myTetrimino.moveRight();

myTetrimino.dataDump();

myTetrimino.moveUp();

myTetrimino.dataDump();

myTetrimino.moveDown();

myTetrimino.dataDump();


}
*/
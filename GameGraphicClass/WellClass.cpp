/*======================================================
Program: Tetris Well
Programmer: Ben Bruser
Date: 2/10/15
Description: Creates a tetris well and allows a 
tetrimino to be copied to the well if appropriate
=======================================================*/
#include "WellClass.h"
#include "TetriminoClass.h"
#include <iostream>

using namespace std;

/*============================================================
Constructor
=============================================================*/
Well::Well()
{
	//sets variables for the height and width
	height = 24; 
	width = 8;
	//loop that populates the board array with blank spaces
	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			board[row][col] = ' ';
		}
	}
}

/*===============================================================
Private Member Function(s)
================================================================*/

/*================================================================
Function Name: rowIsFull
Description: Determines if a row is full or not
Arguments: row (int) - the current row
Return: bool (true or false)
=================================================================*/
bool Well::rowIsFull(int row)
{
	//index counter to count the number of non blank spaces in the row
	int index = 0;
	for(int col = 0; col < width; col++)
	{
		if(board[row][col] != ' ')
		{
			//increases the counter everytime it detects a non blank space
			index++;
		}
	}
	//if the counter reaches 8 (the width of the board) it calls the moveRowsDown function and breaks the loop
	if(index == 8)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*=============================================================
Accessors
==============================================================*/

/*
Function Name: getBoard
Description: Copies the board into a new 2d array
Arguments: boardOut[][8] (char)
Return: none
*/
void Well::getBoard(char boardOut[][8])
{
	//For loop that copies the board into a new 2d char array
	for (int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			boardOut[row][col] = board[row][col];
		}
	}
}

/*===============================================================
Mutators
================================================================*/

/*===============================================================
Function Name: tetriminoFit
Description: determines if the tetrimino will fit at the location on the board
Arguments: object of the Tetrimino class
Return: bool (true or false)
================================================================*/
bool Well::tetriminoFit(Tetrimino myTetrimino)
{
	//create variables for myTetrimino.location, myTetrimino.grid
	int Array[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	myTetrimino.getGrid(Array);
	Location myLocation = myTetrimino.getLocation();

	for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
	{
		for(int col = 0; col < TETRIMINO_GRID_SIZE; col++)
		{
			if(Array[row][col] == 1)
			{
				if(board[myLocation.row + row][myLocation.col + col] != ' ')
				{
					return false;
				}
				if((myLocation.row + row) > 23 || (myLocation.col + col) > 7 ||  (myLocation.col + col) < 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

/*==============================================================
Function Name: addTetriminoToWell
Description: adds the tetrimino piece to the board
Arguments: object of the Tetrimino class
Return: none
================================================================*/
void Well::addTetriminoToWell(Tetrimino myTetrimino)
{
	//Variables for Tetrimino grid, color, location, and the tetriminoFit result
	int Array[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	char tetColor = myTetrimino.getColor();
	myTetrimino.getGrid(Array);
	Location myLocation = myTetrimino.getLocation();
	bool tetFit;
	tetFit = tetriminoFit(myTetrimino);

	if(tetFit == true)
	{
		for(int row = 0; row < TETRIMINO_GRID_SIZE; row++)
		{
			for(int col = 0; col < TETRIMINO_GRID_SIZE; col++)
			{
				if(Array[row][col] == 1)
				{
					board[myLocation.row + row][myLocation.col + col] = tetColor;
				}
			}
		}
	}
}

/*===============================================================
Function Name: clearFullRows
Description: Clears the full row
Arguments: none
Return: rowsCleares(int) - keeps track of the number of rows cleared
================================================================*/
int Well::clearFullRows()
{
	//Loop to check if row is full
	int rowsCleared = 0; 
	for(int row = 0; row < height; row++)
	{
		if(rowIsFull(row))
		{
			moveRowsDown(row);
			rowsCleared++;
		}
	}
	return rowsCleared;
}

/*===============================================================
Function Name: topReached
Description: Determines if the top row has been reached
Arguments: none
Return: bool (true or false)
================================================================*/
bool Well::topReached()
{
	for(int row = 0; row < 1; row++)
	{
		for(int col = 0; col < width; col++)
		{
			if(board[row][col] != ' ')
			{
				return true;
			}
		}
	}
	return false;
}

/*================================================================
Others
=================================================================*/

/*==================================================================
Function Name: moveRowsDown
Description: copies the row above the current row if the event the row is cleared
Arguments: row (int) - the current row
Return: none
===================================================================*/
void Well::moveRowsDown (int row)
{
	// Moves all the upper lines one row down, starting from the 
	// row that was full from the rowIsFull() function and counts up
	for (;row >= 0; row--)
	{
		for (int col = 0; col < width; col++)
		{
			//copies the row above the current row into the current row
			board[row][col] = board[row-1][col];
		}
	}   
	//clears the top row of the board to all blank spaces
	for(int toprow = 0; toprow < 1; toprow++)
	{
		for(int col = 0; col < width; col++)
		{
			board[toprow][col] = ' ';
		}
	}
}

/*==================================================================
Function Name: boardDump
Description: prints out the board to the console
Arguments: none
Return: none
===================================================================*/
void Well::boardDump()
{
	{
		for (int row = 0; row < height; row++)
		{
			for(int col = 0; col < width; col++)
			{
				cout << board[row][col];
			}
			cout << endl;
		}
	}
}
/*
void main()
{
	Tetrimino myTetrimino;
	Well myWell;
	myWell.boardDump();
	myWell.addTetriminoToWell(myTetrimino);
	cout << endl;
	myWell.boardDump();
}
*/
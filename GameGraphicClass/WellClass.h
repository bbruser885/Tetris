/*
Program: Tetris Well!
Programmer: Ben Bruser
Date: 2/10/15
Description: Creates a tetris well and allows a 
tetrimino to be copied to the well if appropriate
*/

#ifndef TETRIS_WELL
#define TETRIS_WELL

#include "TetriminoClass.h"

class Well
{
private:
	int height;
	int width;
	char board[24][8];
	bool rowIsFull(int row);
public:
	//Contructor
	Well();

	//Accesors
	void getBoard(char boardOut[][8]);

	//Mutators
	bool tetriminoFit(Tetrimino myTetrimino);
	void addTetriminoToWell(Tetrimino myTetrimino);
	int clearFullRows();
	bool topReached();

	//Others
	void boardDump();
	void moveRowsDown(int row);
};
#endif
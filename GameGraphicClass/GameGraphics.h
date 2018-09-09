/*======================================================
Program: Game Graphics
Programmer: Ben Bruser
Date: 2/15/15
Description: Creates the graphics for the tetris game!
=======================================================*/
#include <SFML/Graphics.hpp>
#include <string.h>
#include "WellClass.h"
#include "TetriminoClass.h"

//Global Constants
const int LAYOUT_WINDOW_WIDTH = 500;
const int LAYOUT_WINDOW_HEIGHT = 700;
const int LAYOUT_BOARD_TOP = 20;
const int LAYOUT_BOARD_LEFT = 280;
const int BLOCK_SIZE_PIXELS = 25;


class Game
{
private:
	sf::Font myFont;
	sf::RenderWindow window;
	Well* gameWell;
	Tetrimino* tetriminoInPlay;
	Tetrimino* tetriminoOnDeck;
	int score;
	int tempScore;
	int scoreArray[10];
	
	//Others
	void processSplashScreen();
	void processGameScreen();
	bool processGameOverScreen();
	sf::Color convertToSfmlColor(char color);
	void drawWell(Well* gameWell, const int x, const int y, const int z);
	void drawTetrimino(Tetrimino* tetriminoInPlay, const int x, const int y, const int z);
	void drawScore(int x, int y, int z);
	void getScore(int x);
	void getTopScores(int x, int scoreArray[]);
	void DisplayScores(int scoreArray[]);

public:
	//Constructor
	Game();
	//public functions
	void playGame();
};


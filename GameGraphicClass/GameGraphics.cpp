/*======================================================
Program: Game Graphics!
Programmer: Ben Bruser
Date: 2/15/15
Description: Creates the graphics for the tetris game!
=======================================================*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "GameGraphics.h"
#include "WellClass.h"
#include "TetriminoClass.h"
#include <fstream>

using namespace std;

/*===============================================================
Constructor
================================================================*/
Game::Game()
{
	//loads a ttf font file
	myFont.loadFromFile("Bangers.ttf");
	if(!myFont.loadFromFile("Bangers.ttf"))
	{
		cout << "Error, could not find file";
	};

	//Initializes tetrimino and game well pointers to NULL
	tetriminoInPlay = NULL;
	tetriminoOnDeck = NULL;
	gameWell = NULL;

	//Initializes score to 0
	score = 0;

	//Initializes a temporary score variable
	tempScore = 0;

	//Initialize array to zero
	for(int i = 0; i < 10; i++)
	{
		scoreArray[i] = 0;
	}

	//creates a display window
	window.create(
		sf::VideoMode(LAYOUT_WINDOW_WIDTH, LAYOUT_WINDOW_HEIGHT), 
		"Tetris 2015", 
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
}

/*===============================================================
Others
================================================================*/

/*================================================================
Function Name: convertToSfmlColor
Description:Converts the random tetrimino block char into a sf::Color value
Arguments: tetriminoInPlay (Tetrimino class)
Return: sf::Color value 
=================================================================*/
sf::Color Game::convertToSfmlColor(char color)
{
	//Switch statements that converts the tetrimino character value to an sf::Color value
	switch(color)	
	{
	case 't':
		return sf::Color::Cyan;
	case 'b':
		return sf::Color::Blue;
	case 'o':
		return sf::Color(255, 128, 0);
	case 'y':
		return sf::Color::Yellow;
	case 'g':
		return sf::Color::Green;
	case 'p':
		return sf::Color::Magenta;
	case 'r':
		return sf::Color::Red;
	default:
		break;
	}
	return sf::Color::Transparent;
}

/*================================================================
Function Name: drawWell
Description: draws the Well into the opened window
Arguments: gameWell(Well class) - LAYOUT_BOARD_TOP (const int) - LAYOUT_BOARD_LEFT (const int) - BLOCK_SIZE_PIXELS (const int)
Return: bool (true or false)
=================================================================*/
void Game::drawWell(Well* gameWell, const int LAYOUT_BOARD_TOP, const int LAYOUT_BOARD_LEFT, const int BLOCK_SIZE_PIXELS)
{
	//draws the game well
	sf::RectangleShape myGameWell;	 
	myGameWell.setSize(sf::Vector2f(8*BLOCK_SIZE_PIXELS, 24*BLOCK_SIZE_PIXELS));  
	myGameWell.setOutlineThickness(2);  
	myGameWell.setOutlineColor(sf::Color(128,128,128));  
	myGameWell.setFillColor(sf::Color::Transparent);  
	myGameWell.setPosition(LAYOUT_BOARD_LEFT, LAYOUT_BOARD_TOP);  

	sf::Texture backTetris;
	sf::Sprite backImage;
	if(!backTetris.loadFromFile("tetrisBack.jpg"))
	{
		cout << "Error loading image";
	}

	backImage.setTexture(backTetris);

	window.draw(backImage);
	window.draw(myGameWell);  

	//array to store the well
	char Array[24][8];
	gameWell->getBoard(Array);

	//draw the one specific block to draw
	sf::RectangleShape myGameBlock;	 
	myGameBlock.setSize(sf::Vector2f(BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS));  
	myGameBlock.setOutlineThickness(1);  
	myGameBlock.setOutlineColor(sf::Color::Black);  
	//myGameBlock.setFillColor(convertToSfmlColor(tetriminoInPlay));  

	for(int row = 0; row < 24; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			if(Array[row][col] != ' ')
			{
				myGameBlock.setPosition(LAYOUT_BOARD_LEFT + (BLOCK_SIZE_PIXELS*col),
					LAYOUT_BOARD_TOP + (BLOCK_SIZE_PIXELS*row));
				myGameBlock.setFillColor(convertToSfmlColor(Array[row][col]));  
				window.draw(myGameBlock);
			}
		}
	}
}

/*================================================================
Function Name: drawTetrimino
Description: draws the tetrimino into the graphics window
Arguments: tetriminInPlay (Tetrimino class) - LAYOUT_BOARD_TOP (const int) - LAYOUT BOARD_LEFT (const int) - BLOCK_SIZE_PIXELS (const int)
Return: void
=================================================================*/
void Game::drawTetrimino(Tetrimino* tetriminoInPlay, const int LAYOUT_BOARD_TOP, const int LAYOUT_BOARD_LEFT, const int BLOCK_SIZE_PIXELS)
{
	//Calls the get grid function
	int Array[4][4];
	tetriminoInPlay->getGrid(Array);

	//draws the piece in play
	sf::RectangleShape pieceInPlay;	 
	pieceInPlay.setSize(sf::Vector2f(BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS));  
	pieceInPlay.setOutlineThickness(1);  
	pieceInPlay.setOutlineColor(sf::Color::Black);  
	pieceInPlay.setFillColor(convertToSfmlColor(tetriminoInPlay->getColor()));  

	//loop that drawns the piece at the specific location on the board
	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(Array[row][col] == 1)
			{
				pieceInPlay.setPosition( LAYOUT_BOARD_LEFT + (tetriminoInPlay->getLocation().col * BLOCK_SIZE_PIXELS) + ( col * BLOCK_SIZE_PIXELS),
					LAYOUT_BOARD_TOP + (tetriminoInPlay->getLocation().row * BLOCK_SIZE_PIXELS) + (row * BLOCK_SIZE_PIXELS)); 
				window.draw(pieceInPlay);  
			}
		}
	}
}

/*================================================================
Function Name: playGame()
Description: Plays the game (duh)
Arguments: none
Return: void
=================================================================*/
void Game::playGame()
{
	//configures music for the game
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	if(!soundBuffer.loadFromFile("tetris.ogg"))
	{
		cout << "error";
	}
	sound.setBuffer(soundBuffer); 

	//Define enum variables
	enum GameState {TETRIS_SPLASH, TETRIS_PLAY, TETRIS_GAME_OVER};

	//Set myState to TETRIS_SPLASH to begin the game with the splash screen
	GameState myState = TETRIS_SPLASH;

	//plays sound
	sound.play();

	while(window.isOpen())
	{
		switch(myState)
		{
		case TETRIS_SPLASH:
			{
				processSplashScreen();
				myState = TETRIS_PLAY;
			}
		case TETRIS_PLAY:
			{
				processGameScreen();
				myState = TETRIS_GAME_OVER;
			}
		case TETRIS_GAME_OVER:
			{
				getTopScores(tempScore, scoreArray);
				processGameOverScreen();
				if(processGameOverScreen() == true)
					myState = TETRIS_PLAY;
				else
					window.close();
			}
		}
	}
}

/*================================================================
Function Name: processSplashScreen()
Description: 
Arguments: none
Return: void
=================================================================*/
void Game::processSplashScreen()
{
	//configure text objects
	sf::Text myText;  
	myText.setFont(myFont); //myFont must already exist!  
	myText.setColor(sf::Color(89,89,89));  
	myText.setStyle(sf::Text::Bold);  
	myText.setString("Tetris!");  
	myText.setCharacterSize(50); // in pixels, not points!  
	myText.setPosition(200, 20); //left and top are integers  

	//configure text objects
	sf::Text myText2;
	myText2.setFont(myFont); //myFont must already exist!  
	myText2.setColor(sf::Color(89,89,89));  
	myText2.setStyle(sf::Text::Bold);  
	myText2.setString("Press Space to Continue!");  
	myText2.setCharacterSize(35); // in pixels, not points!  
	myText2.setPosition(90, 70); //left and top are integers  

	//configure background image
	sf::Texture backTexture;
	sf::Sprite backImage;
	if(!backTexture.loadFromFile("tetrisBack.jpg"))
	{
		cout << "Error loading image";
	}
	backImage.setTexture(backTexture);



	//Splash Window
	while(window.isOpen())
	{
		sf::Event splashEvent;
		while(window.pollEvent(splashEvent))
		{
			if (splashEvent.type == sf::Event::Closed)  
				window.close();  

			if (splashEvent.type == sf::Event::KeyPressed  
				&& splashEvent.key.code == sf::Keyboard::Space)  
				return;
		}
		//draws things to splash screen
		window.clear(sf::Color::White);
		window.draw(backImage);
		window.draw(myText);
		window.draw(myText2);

		//call DisplayScores function
		DisplayScores(scoreArray);
		window.display();
	}

}

/*================================================================
Function Name: processGameScreen
Description: The code that runs the main game
Arguments: none
Return: void
=================================================================*/
void Game::processGameScreen()
{
	//define variables and allocate memory
	tetriminoInPlay = new Tetrimino;
	tetriminoOnDeck = new Tetrimino;
	gameWell = new Well;
	int counter = 0;
	int difficulty = 30;
	bool top =  gameWell->topReached();

	//defines clock and time objects for difficulty increase
	sf::Clock clock;
	sf::Time elapsed;

	//Game Loop
	while (window.isOpen() && top == false)  
	{  
		// check for and handle events  
		//read and process all events that have occurred  
		// since the last time we checked  

		sf::Event event;  
		while (window.pollEvent(event))
		{  
			//was Window's close button pressed?  
			if (event.type == sf::Event::Closed)  
				window.close();  

			//move left  
			if (event.type == sf::Event::KeyPressed  
				&& event.key.code == sf::Keyboard::Left)  
				tetriminoInPlay->moveLeft();
			if(gameWell->tetriminoFit(*tetriminoInPlay) == false)
			{
				tetriminoInPlay->moveRight();
			}

			//move right
			if (event.type == sf::Event::KeyPressed  
				&& event.key.code == sf::Keyboard::Right)  
				tetriminoInPlay->moveRight();
			if(gameWell->tetriminoFit(*tetriminoInPlay) == false)
			{
				tetriminoInPlay->moveLeft();
			}

			//moves piece down
			if (event.type == sf::Event::KeyPressed  
				&& event.key.code == sf::Keyboard::Down)  
				tetriminoInPlay->moveDown();
			if(gameWell->tetriminoFit(*tetriminoInPlay) == false)
			{
				tetriminoInPlay->moveUp();
			}

			//rotate tetrimino
			if (event.type == sf::Event::KeyPressed  
				&& event.key.code == sf::Keyboard::Up)  
				tetriminoInPlay->rotateRight();
			if(gameWell->tetriminoFit(*tetriminoInPlay) == false)
			{
				tetriminoInPlay->rotateLeft();
			}
		}
		//Counter system to continuously move the tetriminoInPlay down 
		counter++;
		if(counter >= difficulty)
		{
			//Moves the piece down when it is time
			tetriminoInPlay->moveDown();

			//checks to see if the piece does not fit
			if(!gameWell->tetriminoFit(*tetriminoInPlay))
			{
				//If it doesn't fit, moves the piece up 
				tetriminoInPlay->moveUp();

				//Adds new tetrimino to the well
				gameWell->addTetriminoToWell(*tetriminoInPlay);

				//deletes allocated memory
				delete tetriminoInPlay;

				//increments score
				getScore(gameWell->clearFullRows());
				//Checks to see if top is reached, returns true if it has
				if(gameWell->topReached() == true)
				{
					//ends the game
					top = true;
				}
				else
				{
					//Otherwise it sets tetriminoInPlay = to the preview tetrimino
					tetriminoInPlay = tetriminoOnDeck;

					//allocates memory for the new tetrimino
					tetriminoOnDeck = new Tetrimino;

					//If that new tetrimino doesn't fit, returns true
					if(gameWell->tetriminoFit(*tetriminoInPlay) == false)
					{
						//ends the game
						top = true;
					}
				}
			}
			//Sets the counter to 0
			counter = 0;

			//Increase difficulty after certain amount of elapsed time
			elapsed = clock.getElapsedTime();
			if(elapsed.asSeconds() >= 45.0f)
			{
				difficulty = 25;
			}
			if(elapsed.asSeconds() >= 90.0f)
			{
				difficulty = 20;
			}
			if(elapsed.asSeconds() >= 125.0f)
			{
				difficulty = 15;
			}
			if(elapsed.asSeconds() >= 180.0f)
			{
				difficulty = 10;
			}
			if(elapsed.asSeconds() >= 210.0f)
			{
				difficulty = 8;
			}
			if(elapsed.asSeconds() >= 240.0f)
			{
				difficulty = 6;
			}
			if(elapsed.asSeconds() >= 270.0f)
			{
				difficulty = 4;
			}
			if(elapsed.asSeconds() >= 300.0f)
			{
				difficulty = 2;
			}
		}
		window.clear(sf::Color(139,139,131));

		//Calls the functions to draw the well and the tetriminos
		drawWell(gameWell, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);
		drawTetrimino(tetriminoOnDeck, 20, 20, BLOCK_SIZE_PIXELS);
		drawTetrimino(tetriminoInPlay, LAYOUT_BOARD_TOP, LAYOUT_BOARD_LEFT, BLOCK_SIZE_PIXELS);
		drawScore(score, 10, 100);
		window.display();
	}
	//holds the score value in a temporay value and sets the score equal to zero
	tempScore = score;
	score = 0;

	//deletes memory allocated for new classes
	delete tetriminoOnDeck;
	delete gameWell;
}

/*================================================================
Function Name: processGameOverScreen()
Description: Provides a game over screen to the user when they lose
Arguments: none
Return: void
=================================================================*/	
bool Game::processGameOverScreen()
{
	//configures a text object
	sf::Text myText;  

	myText.setFont(myFont); //myFont must already exist!  
	myText.setColor(sf::Color(89,89,89));  
	myText.setStyle(sf::Text::Bold);  
	myText.setString("Game Over");  
	myText.setCharacterSize(50); // in pixels, not points!  
	myText.setPosition(150, 20); //left and top are integers 

	//Configure a text object
	sf::Text myText2;

	myText2.setFont(myFont); //myFont must already exist!  
	myText2.setColor(sf::Color(89,89,89));  
	myText2.setStyle(sf::Text::Bold);  
	myText2.setString("Press Space to Play Again!");  
	myText2.setCharacterSize(35); // in pixels, not points!  
	myText2.setPosition(60, 70); //left and top are integers  

	//Sets background image
	sf::Texture backGame;
	sf::Sprite backImage;
	if(!backGame.loadFromFile("tetrisBack.jpg"))
	{
		cout << "Error loading image";
	}
	backImage.setTexture(backGame);

	//while loop to poll events
	while(window.isOpen())
	{

		sf::Event GameOverEvent;  
		while (window.pollEvent(GameOverEvent))
		{  
			if (GameOverEvent.type == sf::Event::Closed)  
				window.close();  

			if (GameOverEvent.type == sf::Event::KeyPressed  
				&& GameOverEvent.key.code == sf::Keyboard::Space)  
				return true;
		}
		//clears the window and then draws to it
		window.clear(sf::Color::White);
		window.draw(backImage);
		window.draw(myText);
		window.draw(myText2);
		DisplayScores(scoreArray);
		window.display();

	}
	drawScore(tempScore, 10, 200);
}

/*================================================================
Function Name: drawScore
Description: Draws the score to the left of the well
Arguments: score (int), left (int), top (int)
Return: void
=================================================================*/	
void Game::drawScore(int score, int left, int top)
{
	//configures a test object
	sf::Text myScore;  

	myScore.setFont(myFont); //myFont must already exist!  
	myScore.setColor(sf::Color(89,89,89));  
	myScore.setStyle(sf::Text::Bold);  
	myScore.setString("You Score is:"); 
	myScore.setCharacterSize(40); // in pixels, not points!  
	myScore.setPosition(left, top); //left and top are integers  
	window.draw(myScore);

	myScore.setString(to_string(score));
	top+=30;
	myScore.setPosition(left,top);

	//draws the integer score
	window.draw(myScore);
}

/*================================================================
Function Name: getScore
Description: gets and modifies the score to display
Arguments: rowsCleared (int)
Return: void
=================================================================*/	
void Game::getScore(int rowsCleared)
{
	//Switch statement that goes through the value returned by rowsCleared and alters them to score.
	switch (rowsCleared)
	{
	case 1: score = score+(40*rowsCleared);
		break;

	case 2: score = score+(50*rowsCleared);
		break;

	case 3: score = score+(100*rowsCleared);
		break;

	case 4: score = score+(300*rowsCleared);
		break;
	}
}

/*================================================================
Function Name: getTopScores
Description: gets the score after the game ends, adds it to the array
then prints the array to a txt file. 
Arguments: tempScore (int) - array[] (int)
Return: void
=================================================================*/	
void Game::getTopScores(int tempScore, int array[])
{
	//Clears the text file everytime the function is called
	ofstream outPutDelete;
	outPutDelete.open("HighScores.txt", ofstream::out | ofstream::trunc);
	outPutDelete.close();

	//Sorts the array
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(array[i] < array[j])
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	//checks the lowest score 
	if(tempScore > array[0])
	{
		array[0] = tempScore;
	}

	//Sorts the array again!
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(array[i] < array[j])
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	//creates a writing stream to the HighScores text file
	ofstream outputFile;  
	outputFile.open("HighScores.txt", ofstream::out | ofstream::app); 

	//writes the data from the array 
	for(int i = 0; i < 10; i++)
	{
		outputFile << array[i] << endl; 
	}

	//close the file 
	outputFile.close(); 
} 

/*================================================================
Function Name: DisplayScores
Description: Gets the input from the txt file 
Arguments: array[] (int)
Return: void
=================================================================*/	
void Game::DisplayScores(int array[])
{
	//declare counter variable
	int i = 0;

	//delcare top value
	int top = 200;
	int left = 210;

	//opens input stream from the HighScores text file
	ifstream inputScores;
	inputScores.open("HighScores.txt");

	//Loop to get the high scores from the file and copy them into the array
	while(inputScores >> array[i])
	{
		i++;
	}

	//creates high score text object
	sf::Text highScore;  

	highScore.setFont(myFont); //myFont must already exist!  
	highScore.setColor(sf::Color(89,89,89));  
	highScore.setStyle(sf::Text::Bold); 
	highScore.setCharacterSize(20); // in pixels, not points!  
	highScore.setString("High Scores!");
	highScore.setPosition(left, top);

	//draw the high score label
	window.draw(highScore);

	//Loops through the array and draws the scores to the splash screen
	for(int j = 9; j  >= 0; j--)
	{
		highScore.setString(to_string(scoreArray[j]));
		top+=25;
		highScore.setPosition(240,top);

		//draws the integer score
		window.draw(highScore);
	}

}
//======================================================================
void main()
{
	Game theGame;
	theGame.playGame();
}
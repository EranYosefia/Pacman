#pragma once
#include "board.h"
#include "pacman.h"
#include "ghost.h"
#include "fruit.h"
#include <conio.h>
#include "smartestMove.h"
#include "noviceMove.h"
#include <sstream>

class Game {
public:

	Game(std::vector<std::string> filenames, bool c = 1, char gameLevel = 0, int operationMode = 0, int lives = 3, int score = 0, int breadCrumbsCounter = 0) :
		_filenames(filenames), _ifColored(c), _gameLevel(gameLevel), _operationMode(operationMode), _lives(lives), _score(score), _breadCrumbsCounter(breadCrumbsCounter) {}

	void start();
	
	void run(Board& board, Pacman& player, std::vector<Ghost>& ghostVec, Fruit& fruit, int& mapIdx, std::string& cmpResult);

	void pauseMode(Board& b);
	//Function handling the case where the user paused the game

	void moveObjOnBoard(Board& b, GameObject& creature);

	void pacEatBread(Board& b, Pacman& player);

	void initGameObj(Board& b, Point& pacStartLocation, std::vector<Ghost>& ghostVec, bool& currectBoard);
	//Function initialize the differnt type of game objects (pacman, ghost and fruit)

	void resetGameObj(Board& b, GameObject& creature);
	//Function reseting game object to his starting point on board

	void printDiffMesg(int& mapIdx);
	//function handling the different kind of messages printed, if the player lost the game/round, won ETC...

	void savingMove(GameObject& creature, int& mapIdx);

private:

	std::vector<std::string> _filenames;

	bool _ifColored;
	
	char _gameLevel;

	int _operationMode;
	// 0 for simple
	// 1 for save
	// 2 for load
	// 3 for load silent

	int _lives;
	int _score;

	int _breadCrumbsCounter;
};
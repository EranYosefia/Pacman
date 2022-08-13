#include "game.h"

void Game::start()
{
	system("cls");
	
	bool currectBoard = true;

	int mapIdx = 0;

	std::vector<std::string> testResult;

	std::string cmpResult = "";

	while (mapIdx < _filenames.size() != 0 && !ifLost(_lives)) {

		Board b(_filenames[mapIdx] + ".screen");

		_breadCrumbsCounter = b.initBreadVec();
		Point pacStartLocation;
		system("cls");

		std::vector<Ghost> ghostVec;

		initGameObj(b, pacStartLocation, ghostVec, currectBoard);

		if (currectBoard) {
			if (_operationMode != 3) {
				b.printBoard(_ifColored);
				b.printStats(_lives, _score);
			}
			Pacman player(pacStartLocation);

			Fruit f(b.findFreePlace(), drawNum5to9());

			if (_operationMode == 2 || _operationMode == 3) {

				int r = 0, ghostCount = -1;
				std::ifstream file(_filenames[mapIdx] + ".steps");

				std::string str, item;
				char ch;
				while (std::getline(file, str))
				{
					std::istringstream a(str);

					a >> item;

					if (strcmp(item.c_str(), "Pacman:") == 0)
						r = 1;
					else if (strcmp(item.c_str(), "Ghost:") == 0) {
						r = 2;
						ghostCount++;
					}
					else
						r = 3;
					while (a >> ch) {

						if (r == 1)
							player.setObjMoveDoc(ch);
						else if (r == 2)
							ghostVec[ghostCount].setObjMoveDoc(ch);
					}
				}
			}
			if (_operationMode == 1)
				std::ofstream outfile(_filenames[mapIdx] + ".result");

			run(b, player, ghostVec, f, mapIdx, cmpResult);

			if (_operationMode == 1) {
				std::ofstream outfile(_filenames[mapIdx] + ".steps");
				savingMove(player, mapIdx);
				for (Ghost g : ghostVec)
					savingMove(g, mapIdx);
			}
			ghostVec.clear();
			mapIdx++;

			if (_operationMode != 2 && _operationMode != 3)
				printDiffMesg(mapIdx);
			else if (_operationMode == 2) {
				system("cls");
				std::cout << "Finished loading...";
			}
			else if (_operationMode == 3) {
				system("cls");
				std::string result;
				std::ifstream file(_filenames[mapIdx - 1] + ".result");

				std::getline(file, result);
				if (result == cmpResult)
					testResult.push_back("Level " + std::to_string(mapIdx) + " TEST PASSED");
				else
					testResult.push_back("Level " + std::to_string(mapIdx) + " TEST FAILED");
				cmpResult = "";
			}
		}
		else {
			mapIdx++;
			currectBoard = true;
		}
	}
	if (_operationMode == 3)
		for (std::string str : testResult)
			std::cout << str << std::endl;
}

void Game::run(Board& board, Pacman& player, std::vector<Ghost>& ghostVec, Fruit& fruit, int& mapIdx, std::string& cmpResult) {

	bool ghostTouchPac = false;
	int slowerTheGhost = 1;
	int fruitLifeCycle = 1;
	char c = 0, lastMove = 0;
	int numOfGhosts = ghostVec.size();
	int loops = 0;
	int countNormalMoves = 0;

	Board::gotoxy(player.getObjLocation().colm, player.getObjLocation().row);

	while (!ifWon(_breadCrumbsCounter) && !ifLost(_lives)) {

		if (_operationMode != 2 && _operationMode != 3) {
			lastMove = c;
			if (_kbhit())
				c = _getch();

			Sleep(90);

			while (!ifValidMove(c) && (lastMove == 0))
				c = _getch();

			if (c == ESC)
				pauseMode(board);

			if (!ifValidMove(c))
				c = lastMove;

			player.setPacmanC(c);
		}
		else {
			player.setPacmanC(player.retAndDel());
			if (_operationMode != 3)
				Sleep(90);
		}

		player.GameObjMove(board, _operationMode);
		if (board.getCellFromBoard(player.getObjLocation()) == '$')
			ghostTouchPac = true;
		moveObjOnBoard(board, player);
		if (_operationMode != 3)
			board.printChanges(player.getObjPreviousLocation(), player.getObjLocation(), _ifColored);

		if (player.getObjLocation() == fruit.getObjLocation() && fruit.getIfFruitShown()) {

			_score += fruit.getObjSymbol() - '0';
			fruitLifeCycle = 0;
		}
		if (countNormalMoves >= 20 && _gameLevel == '2') {

			for (int i = 0; i < numOfGhosts; i++) {
				Strategy* s = nullptr;
				if (countNormalMoves == 24) {
					s = new SmartestMove;
					ghostVec[i].setLevel(s);
				}
				else {
					s = new NoviceMove;
					ghostVec[i].setLevel(s);
				}
			}
			if (countNormalMoves == 24)
				countNormalMoves = 0;
		}
		countNormalMoves++;

		if (/*slowerTheGhost % 2 == 0 && */!ghostTouchPac) {
			for (int i = 0; i < numOfGhosts; i++) {
				ghostVec[i].GameObjMove(board, _operationMode);
				if (player.getObjLocation() == ghostVec[i].getObjLocation())
					ghostTouchPac = true;
				moveObjOnBoard(board, ghostVec[i]);
				if (_operationMode != 3)
					board.printChanges(ghostVec[i].getObjPreviousLocation(), ghostVec[i].getObjLocation(), _ifColored);

				if (ghostVec[i].getObjLocation() == fruit.getObjLocation() && !fruit.getIfFruitShown())
					fruitLifeCycle = 0;
			}
		}slowerTheGhost++;

		if (fruit.getIfFruitShown() && fruitLifeCycle != 0) {

			fruit.GameObjMove(board, _operationMode);
			moveObjOnBoard(board, fruit);
			if (_operationMode != 3)
				board.printChanges(fruit.getObjPreviousLocation(), fruit.getObjLocation(), _ifColored);
		}

		if (ghostTouchPac) {

			_lives--;

			resetGameObj(board, player);

			for (int i = 0; i < numOfGhosts; i++)
				resetGameObj(board, ghostVec[i]);

			fruitLifeCycle = 0;
			if (_operationMode != 3) {
				system("cls");
				board.printBoard(_ifColored);
			}
			ghostTouchPac = false;
			c = 0;

			if (_operationMode == 1) {
				std::ofstream outfile;
				outfile.open(_filenames[mapIdx] + ".result", std::ios_base::app);
				outfile << "death: " << loops << " ";
			}
			else if (_operationMode == 2 || _operationMode == 3)
				cmpResult += "death: " + std::to_string(loops) + " ";
		}
		pacEatBread(board, player);

		if (fruitLifeCycle % 70 == 0) {

			board.setCellFromBoard(board.getCellFromBreadVec(fruit.getObjLocation()), fruit.getObjLocation());
			if (_operationMode != 3)
				board.printChanges(fruit.getObjPreviousLocation(), fruit.getObjLocation(), _ifColored);
			fruit.setIfFruitShown(!fruit.getIfFruitShown());
			fruit.setObjLocation(board.findFreePlace());

			fruit.setObjSymbol(drawNum5to9());

		}fruitLifeCycle++;

		if (_operationMode != 3)
			board.printStats(_lives, _score);

		loops++;
	}
	if (_operationMode == 1) {
		std::ofstream outfile;
		outfile.open(_filenames[mapIdx] + ".result", std::ios_base::app);
		outfile << "finish: " << loops << " ";
	}
	else if (_operationMode == 2 || _operationMode == 3)
		cmpResult += "finish: " + std::to_string(loops) + " ";
}

	void Game::pauseMode(Board& b) {

	char c = 0;
	while (c != ESC) {
		Board::gotoxy(b.getstatsPrintPosition().colm, b.getstatsPrintPosition().row);
		std::cout << " GAME PAUSED ";

		Board::gotoxy(b.getstatsPrintPosition().colm, b.getstatsPrintPosition().row + 1);
		std::cout << " press ESC to back ";
		c = _getch();
	}
	Board::gotoxy(b.getstatsPrintPosition().colm, b.getstatsPrintPosition().row);
	std::cout << "####################";
	Board::gotoxy(b.getstatsPrintPosition().colm, b.getstatsPrintPosition().row + 1);
	std::cout << "####################";
}

void Game::pacEatBread(Board& b, Pacman& player) {

	if (b.getCellFromBreadVec(player.getObjLocation()) == '*') {
		_score++;
		_breadCrumbsCounter--;
		b.setCellFromBreadVec(player.getObjLocation());
	}
}

void Game::moveObjOnBoard(Board& b, GameObject& creature) {

	b.setCellFromBoard(b.getCellFromBreadVec(creature.getObjPreviousLocation()), creature.getObjPreviousLocation());
	b.setCellFromBoard(creature.getObjSymbol(), creature.getObjLocation());
}

void Game::resetGameObj(Board& b, GameObject& creature) {

	creature.setObjPreviousLocation(creature.getObjLocation());
	creature.setObjLocation(creature.getObjStartingLocation());
	moveObjOnBoard(b, creature);
}

void Game::initGameObj(Board& b, Point& pacStartLocation, std::vector<Ghost>& ghostVec, bool& currectBoard) {

	int currRow, currColm;

	int bRows = b.getRowsOfBoard();
	int bColms = b.getColmsOfBoard();

	int pacmanCounter = 0, ghostCounter = 0;

	for (int i = 0; i < bRows * bColms; i++) {

		currRow = i / bColms;
		currColm = i - (currRow * bColms);

		if (b.getCellFromBoard({ currRow ,currColm }) == '@') {
			pacStartLocation = { currRow, currColm };
			pacmanCounter++;
		}
		else if (b.getCellFromBoard({ currRow ,currColm }) == '$') {
			Strategy* s = nullptr;
			if (_gameLevel == '1')
				s = new NoviceMove;
			else
				s = new SmartestMove;
	
			ghostVec.push_back({ { currRow ,currColm }, '$' , s });
			ghostCounter++;
		}		
	}
	if (pacmanCounter != 1 || ghostCounter > 4)
		currectBoard = false;
}

void Game::printDiffMesg(int& mapIdx) {

	system("cls");

	if (_lives == 0) {

		std::cout << "~GAME OVER~" << std::endl;
		std::cout << "Press any key in order to return to the menu";
		char c = 0;
		c = _getch();
	}
	else {
		if (mapIdx < _filenames.size()) {
			std::cout << "You have passed stage " << mapIdx + 1 << std::endl;
			std::cout << "you are mooving to the next stage";
			Sleep(2000);

		}
		else {
			std::cout << "Congratulations, You Won!" << std::endl;
			std::cout << "Press any key in order to return to the menu";
			char c = 0;
			c = _getch();
		}
	}
}

void Game::savingMove(GameObject& creature,int& mapIdx) {

	std::ofstream outfile;

	outfile.open(_filenames[mapIdx] + ".steps", std::ios_base::app);

	if (creature.getObjSymbol() == '@')
		outfile << "Pacman: ";
	else if (creature.getObjSymbol() == '$')
		outfile << "Ghost: ";
	else
		outfile << "Fruit: ";

	for (char s : creature.getObjMoveDoc()) {

		outfile << s << " ";
	}
	outfile << std::endl;

	outfile.close();
}
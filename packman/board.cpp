#include "board.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Board::Board(const std::string& mapName) {
	
	int colms = 0;
	int rows = 0;
	int i = 0;
	
	std::ifstream file(mapName);
	
	std::string line;
	while (getline(file, line))
	{
		while (line[i] != '\0') {

			_board.push_back(line[i]);
			i++;
			if (rows == 0)
				colms++;
		}
		rows++;
		i = 0;
		_board.push_back('\n');

	}
	colms++;
	
	_rows = rows;
	_colms = colms;
	_board.resize(rows * colms);
	int breadCrumbsCounter = 0;
	
	_breadCrumbsVec.resize(_rows * _colms);
	_visited.resize(rows * colms);
	
	for (int i = 0; i < _rows * _colms; i++) {
		if (_board[i] == ' ') {
			_board[i] = '*';
			_breadCrumbsVec[i] = '*';
			breadCrumbsCounter++;
			_visited[i] = false;
		}
		else if (_board[i] == '%') {

			_board[i] = ' ';
			_breadCrumbsVec[i] = ' ';
			_visited[i] = false;
		}
		else if (_board[i] == '&') {
			
			_statsPrintPosition.row = i / _colms;
			_statsPrintPosition.colm = i - _statsPrintPosition.row * _colms;
			_visited[i] = true;
		}
		else {
			_breadCrumbsVec[i] = ' ';
			if (_board[i] == '$' || _board[i] == '@' || _board[i] == '\n')
				_visited[i] = false;
			else
				_visited[i] = true;
		}
	}
}

char Board::getCellFromBoard(Point p) const {

	return _board[p.colm + p.row * _colms];
}

void Board::setCellFromBoard(char value, Point p) {

	_board[p.colm + p.row * _colms] = value;
}


void Board::printBoard(bool ifColored) const {
	if (ifColored)
	{
		for (int i = 0; i < _rows * _colms; i++) {

			if (_board[i] == '*') {

				SetConsoleTextAttribute(hConsole, BLUE);
				std::cout << _board[i];
			}
			else if (_board[i] == '@') {

				SetConsoleTextAttribute(hConsole, GOLD);
				std::cout << _board[i];
			}
			else if (_board[i] == '$') {

				SetConsoleTextAttribute(hConsole, RED);
				std::cout << _board[i];
			}
			else {
				SetConsoleTextAttribute(hConsole, WHITE);
				std::cout << _board[i];
			}
		}
	}
	else {
		for (int i = 0; i < _rows * _colms; i++)
			std::cout << _board[i];
	}
}

void Board::printChanges(Point prevLoc, Point curLoc, bool ifColored) {
	
	if (ifColored)
	{
		gotoxy(prevLoc.colm, prevLoc.row);
		if (_board[prevLoc.colm + prevLoc.row * _colms] == '*') {
			SetConsoleTextAttribute(hConsole, BLUE);
			std::cout << _board[prevLoc.colm + prevLoc.row * _colms];
		}
		else if (_board[prevLoc.colm + prevLoc.row * _colms] == '@') {
			SetConsoleTextAttribute(hConsole, GOLD);
			std::cout << _board[prevLoc.colm + prevLoc.row * _colms];
		}
		else if (_board[prevLoc.colm + prevLoc.row * _colms] == '$') {
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << _board[prevLoc.colm + prevLoc.row * _colms];
		}
		else
		{
			SetConsoleTextAttribute(hConsole, WHITE);
			std::cout << _board[prevLoc.colm + prevLoc.row * _colms];
		}

		gotoxy(curLoc.colm, curLoc.row);
		if (_board[curLoc.colm + curLoc.row * _colms] == '*') {
			SetConsoleTextAttribute(hConsole, BLUE);
			std::cout << _board[curLoc.colm + curLoc.row * _colms];
		}
		else if (_board[curLoc.colm + curLoc.row * _colms] == '@') {
			SetConsoleTextAttribute(hConsole, GOLD);
			std::cout << _board[curLoc.colm + curLoc.row * _colms];
		}
		else if (_board[curLoc.colm + curLoc.row * _colms] == '$') {
			SetConsoleTextAttribute(hConsole, RED);
			std::cout << _board[curLoc.colm + curLoc.row * _colms];
		}
		else
		{
			SetConsoleTextAttribute(hConsole, WHITE);
			std::cout << _board[curLoc.colm + curLoc.row * _colms];
		}
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	else {

		gotoxy(prevLoc.colm, prevLoc.row);
		std::cout << _board[prevLoc.colm + prevLoc.row * _colms];
		gotoxy(curLoc.colm, curLoc.row);
		std::cout << _board[curLoc.colm + curLoc.row * _colms];
	}
}

void Board::printStats(int& lives, int& score) const {
	
	gotoxy(_statsPrintPosition.colm, _statsPrintPosition.row);
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << " LIVES: " << lives << " ";
	gotoxy(_statsPrintPosition.colm, _statsPrintPosition.row+1);
	std::cout << " SCORE: " << score << " ";
}

 void Board::gotoxy(short x, short y)
{
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x, y };
	std::cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

 int Board::initBreadVec() {

	 int breadCrumbsCounter = 0;
	 _breadCrumbsVec.resize(_rows * _colms);
	 
	 for (int i = 0; i < _rows * _colms; i++) {
		 if (_board[i] == '*') {

			 _breadCrumbsVec[i] = '*';
			 breadCrumbsCounter++;
		 }
		 else {
			 _breadCrumbsVec[i] = ' ';
		 }
	 }
	 return breadCrumbsCounter;
 }

 char Board::getCellFromBreadVec(Point p) const {

	 return _breadCrumbsVec[p.colm + p.row * _colms];

 }

 void Board::setCellFromBreadVec(Point p) {

	 _breadCrumbsVec[p.colm + p.row * _colms] = ' ';
 }

 int Board::getRowsOfBoard() const {

	 return _rows;
 }

 int Board::getColmsOfBoard() const {

	 return _colms;
 }

 Point Board::findFreePlace() {
	 
	 int drawedRow, drawedColm;
	 
	// srand((unsigned int)time(NULL));
	 do {
		 drawedRow = rand() % (_rows - 1) + 1;
		 drawedColm = rand() % (_colms - 2) + 1;
	 } while (_board[drawedColm + drawedRow * _colms] != '*' &&
		 _board[drawedColm + drawedRow * _colms] != ' ');

	 return  { drawedRow,drawedColm };

 }

 Point Board::getstatsPrintPosition() const {

	 return _statsPrintPosition;
 }

 bool Board::getVisited(Point p) const {

	 return _visited[p.colm + p.row * _colms];
 }

 std::vector<bool> Board::getAllVisitedBoard() const{

	 return _visited;
 }
#include "ghost.h"

void Ghost::GameObjMove(Board& b, int opMode) {

	int c = 0;
	Point cur = _gameObjLocation;
	Point prev = _gameObjPreviousLocation;

	if (opMode != 2 && opMode != 3) {
		_level->moveStrategy(b, cur, prev, c);
		
		convertDirToStr(c);
	}
	else {

		char ch;
		int dirR = 0, dirC = 0;

		ch = retAndDel();
		determineDirections(ch, dirR, dirC);
		if (b.getCellFromBoard({ cur.row + dirR, cur.colm + dirC }) != '#') {

			prev.row = cur.row;
			prev.colm = cur.colm;



			if (b.getCellFromBoard({ cur.row + dirR, cur.colm + dirC }) != '$') {
				cur.row += dirR;
				cur.colm += dirC;
			}
		}
	}

	if (!ifInTunnel(b, 0, cur.row, cur.colm)) {
		_gameObjLocation = cur;
		_gameObjPreviousLocation = prev;
	}
	else {

		_gameObjPreviousLocation = _gameObjLocation;
	}
}

void Ghost::setLevel(Strategy* level) {

	_level = level;
}

bool Ghost::ifInTunnel(Board& b, char c, int& dirR, int& dirC) {

	if (dirC == 0 || dirC == b.getColmsOfBoard() - 2 ||
		dirR == 0 || dirR == b.getRowsOfBoard() - 1)
	{
		return true;
	}
	return false;
}
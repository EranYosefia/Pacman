#include "fruit.h"

void Fruit::GameObjMove(Board& b, int opMode)
{

	int c = 0;
	int wall = 0;
	int dirR = 0, dirC = 0;

	//srand((unsigned int)time(NULL));
	do {

		c = rand() % 4;

		determineDirections(c, dirR, dirC);

		if (b.getCellFromBoard({ _gameObjLocation.row + dirR, _gameObjLocation.colm + dirC }) != '#' &&
			!ifInTunnel(b, c, dirR, dirC) && b.getCellFromBoard({ _gameObjLocation.row + dirR, _gameObjLocation.colm + dirC }) != '$')
			wall = 1;
	} while (wall == 0);

	_gameObjPreviousLocation.row = _gameObjLocation.row;
	_gameObjPreviousLocation.colm = _gameObjLocation.colm;

	if (b.getCellFromBoard({ _gameObjLocation.row + dirR, _gameObjLocation.colm + dirC }) != '@') {
		_gameObjLocation.row += dirR;
		_gameObjLocation.colm += dirC;
	}
	if (opMode != 3 && opMode != 2)
		convertDirToStr(c);
}

bool Fruit::getIfFruitShown() {

	return _ifFruitShown;
}

void Fruit::setIfFruitShown(bool ifFruitShown) {

	_ifFruitShown = ifFruitShown;
}

bool Fruit::ifInTunnel(Board& b, char c, int& dirR, int& dirC) {

	if (_gameObjLocation.colm + dirC == 0 || _gameObjLocation.colm + dirC == b.getColmsOfBoard() - 2 ||
		_gameObjLocation.row + dirR == 0 || _gameObjLocation.row + dirR == b.getRowsOfBoard() - 1)
	{
		return true;
	}
	return false;
}

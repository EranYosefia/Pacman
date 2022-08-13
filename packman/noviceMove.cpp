#include "noviceMove.h"


void NoviceMove::moveStrategy(Board& b, Point& curPosition, Point& prevPosition, int& cd) {

	int c;
	int wall = 0;
	int dirR = 0, dirC = 0;

	//srand((unsigned int)time(NULL));
	do {

		c = rand() % 4;

		determineDirections(c, dirR, dirC);

		if (b.getCellFromBoard({ curPosition.row + dirR, curPosition.colm + dirC }) != '#')
			wall = 1;
	} while (wall == 0);

	prevPosition.row = curPosition.row;
	prevPosition.colm = curPosition.colm;

	if (b.getCellFromBoard({ curPosition.row + dirR, curPosition.colm + dirC }) != '$') {
		curPosition.row += dirR;
		curPosition.colm += dirC;
	}
	cd = c;
}
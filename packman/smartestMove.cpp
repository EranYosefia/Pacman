#include "smartestMove.h"

void SmartestMove::moveStrategy(Board& b, Point& curPosition, Point& prevPosition, int& cd) {

	int minDistance = 5000, distance = 0;
	char minDirection = 0;
	int dirR = 0, dirC = 0;
	
	std::vector<char> directionOp = { LEFT,RIGHT,UP,DOWN };

	for (int i = 0; i < directionOp.size(); i++) {

		determineDirections(directionOp[i], dirR, dirC);

		if (b.getCellFromBoard({ curPosition.row + dirR,curPosition.colm + dirC }) == '@') {
			cd = directionOp[i];
			prevPosition = curPosition;
			curPosition = { curPosition.row + dirR,curPosition.colm + dirC };
			return;
		}
		else if (b.getCellFromBoard({ curPosition.row + dirR,curPosition.colm + dirC }) == '#' ||
			b.getCellFromBoard({ curPosition.row + dirR,curPosition.colm + dirC }) == '$') {}
		else {

			distance = minDist(b, b.getAllVisitedBoard(), { curPosition.row + dirR,curPosition.colm + dirC });

			if (distance <= minDistance && distance >= 0) {
				minDistance = distance;
				minDirection = directionOp[i];
			}
		}
		dirR = 0, dirC = 0;
		distance = 0;
	}
	if (minDirection != 0) {
		determineDirections(minDirection, dirR, dirC);
		prevPosition = curPosition;
		curPosition = { curPosition.row + dirR,curPosition.colm + dirC };
		
	}
	cd = minDirection;
}

int SmartestMove::minDist(Board& b, std::vector<bool> visited, Point possibleNextLoc) {

	int boardRows = b.getRowsOfBoard();
	int boardColms = b.getColmsOfBoard();

	QItem source(possibleNextLoc.row, possibleNextLoc.colm, 0);

	std::queue<QItem> q;
	q.push(source);

	visited[source.colm + source.row* boardColms] = true;
	
	
	while (!q.empty()) {
		QItem p = q.front();
		q.pop();

		if (b.getCellFromBoard({ p.row,p.colm }) == '@')
			return p.dist;


		if (p.row - 1 >= 0 &&
			visited[p.colm + (p.row - 1) * boardColms] == false) {
			q.push(QItem(p.row - 1, p.colm, p.dist + 1));
			visited[p.colm + (p.row - 1) * boardColms] = true;
		}

		if (p.row + 1 < boardRows &&
			visited[p.colm + (p.row + 1) * boardColms] == false) {
			q.push(QItem(p.row + 1, p.colm, p.dist + 1));
			visited[p.colm + (p.row + 1) * boardColms] = true;
		}

		if (p.colm - 1 >= 0 &&
			visited[(p.colm - 1) + p.row * boardColms] == false) {
			q.push(QItem(p.row, p.colm - 1, p.dist + 1));
			visited[(p.colm - 1) + p.row * boardColms] = true;
		}

		if (p.colm + 1 < boardColms &&
			visited[(p.colm + 1) + p.row * boardColms] == false) {
			q.push(QItem(p.row, p.colm + 1, p.dist + 1));
			visited[(p.colm + 1) + p.row * boardColms] = true;
		}
	}
	return -1;

}
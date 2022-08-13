#include "gameObject.h"

void GameObject::setObjStartingLocation(Point p) {

	_gameObjStartingLocation.row = p.row;
	_gameObjStartingLocation.colm = p.colm;
}

void GameObject::setObjLocation(Point p) {

	_gameObjLocation.row = p.row;
	_gameObjLocation.colm = p.colm;
}

void GameObject::setObjPreviousLocation(Point p) {

	_gameObjPreviousLocation.row = p.row;
	_gameObjPreviousLocation.colm = p.colm;
}

void GameObject::setObjSymbol(char symbol) {

	_symbol = symbol;

}

Point GameObject::getObjStartingLocation() const {

	return _gameObjStartingLocation;
}

Point GameObject::getObjLocation() const {

	return _gameObjLocation;
}

char GameObject::getObjSymbol() const {

	return _symbol;
}

Point GameObject::getObjPreviousLocation() const {

	return _gameObjPreviousLocation;
}

void GameObject::convertDirToStr(int c) {

	if (c == RIGHT || c == right || c == 0)
		objMoveDoc.push_back('R');
	else if (c == LEFT || c == left || c == 1)
		objMoveDoc.push_back('L');
	else if (c == UP || c == up || c == 2)
		objMoveDoc.push_back('U');
	else if (c == DOWN || c == down || c == 3)
		objMoveDoc.push_back('D');
	else if (c == STAY || c == stay)
		objMoveDoc.push_back('S');
}

std::vector<char> GameObject::getObjMoveDoc() const {

	return objMoveDoc;
}

void GameObject::setObjMoveDoc(char ch) {

	if (ch == 'R')
		ch = 0;
	else if (ch == 'L')
		ch = 1;
	else if (ch == 'U')
		ch = 2;
	else if (ch == 'D')
		ch = 3;
	else if (ch == 'S')
		ch = 4;
	objMoveDoc.push_back(ch);
}

void GameObject::GameObjMoveLoadMode(Board& b) {

	int dirR = 0, dirC = 0;

	char c;
	c = retAndDel();
	determineDirections(c, dirR, dirC);

	ifInTunnel(b, c, dirR, dirC);

	if (b.getCellFromBoard({ _gameObjLocation.row + dirR, _gameObjLocation.colm + dirC }) != '#') {

		_gameObjPreviousLocation.row = _gameObjLocation.row;
		_gameObjPreviousLocation.colm = _gameObjLocation.colm;
		if (b.getCellFromBoard({ _gameObjLocation.row + dirR, _gameObjLocation.colm + dirC }) != '$') {
			_gameObjLocation.row += dirR;
			_gameObjLocation.colm += dirC;
		}
	}
}

char GameObject::retAndDel() {

	char c;
	if (objMoveDoc.size() == 0)
		c = 'S';
	else {
		c = objMoveDoc.front();
		objMoveDoc.erase(objMoveDoc.begin());
	}
	return c;
}
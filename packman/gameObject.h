#pragma once
#include "definitions.h"
#include "validation.h"
#include "board.h"

class GameObject {

public:
	void setObjStartingLocation(Point p);
	void setObjLocation(Point p);
	void setObjPreviousLocation(Point p);
	void setObjSymbol(char symbol);
	void setObjMoveDoc(char ch);

	Point getObjStartingLocation() const;
	Point getObjLocation() const;
	Point getObjPreviousLocation() const;
	char getObjSymbol() const;
	std::vector<char> getObjMoveDoc() const;

	void convertDirToStr(int c);

	char retAndDel();
	
	virtual bool ifInTunnel(Board& b, char c, int& dirR, int& dirC) = 0;

	virtual void GameObjMove(Board& b, int opMode) = 0;

	void GameObjMoveLoadMode(Board& b);

	GameObject(Point p1, Point p2, Point p3, char symbol) :
		_gameObjStartingLocation(p1), _gameObjLocation(p2), _gameObjPreviousLocation(p3), _symbol(symbol) {}

	//bool operator==(const GameObject& obj) { return _gameObjLocation == obj.getObjLocation(); }

protected:
	Point _gameObjStartingLocation;
	Point _gameObjLocation;
	Point _gameObjPreviousLocation;
	char _symbol;

	std::vector<char> objMoveDoc;
};
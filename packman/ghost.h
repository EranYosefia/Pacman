#pragma once
#include "gameObject.h"
#include "strategy.h"

class Ghost : public GameObject {
public:

	virtual void GameObjMove(Board& b, int opMode);

	void setLevel(Strategy* level);
	//Function sets game level in colaration with the level of the ghost

	virtual bool ifInTunnel(Board& b, char c, int& dirR, int& dirC);

	Ghost(Point p, char symbol, Strategy* level) : GameObject(p, p, p, symbol), _level(level) {}
	
private:

	Strategy* _level;
};
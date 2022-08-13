#pragma once
#include "gameObject.h"

class Pacman : public GameObject {
public:

	void setPacmanC(char c);

	virtual void GameObjMove(Board& b, int opMode);

	virtual bool ifInTunnel(Board& b, char c, int& dirR, int& dirC);

	Pacman(Point p = { 0,0 } , char symbol = '@', char c = 0) : GameObject(p, p, p, symbol), _c(c) {}

private:

	char _c;
};
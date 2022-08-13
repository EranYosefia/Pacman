#pragma once
#include "gameObject.h"

class Fruit : public GameObject {
public:

	virtual void GameObjMove(Board& b, int opMode);
	// Virtual function implemnting an object movement on board

	bool getIfFruitShown();
	// Function returns whether the fruit is currently shown on the board

	void setIfFruitShown(bool ifFruitShown);

	Fruit(Point p, char symbol, bool ifFruitShown = true) : GameObject(p, p, p, symbol), _ifFruitShown(ifFruitShown) {}
	// fruit Ctor

	virtual bool ifInTunnel(Board& b, char c, int& dirR, int& dirC);
	// Virtual function checks whether an object is about to enter a tunnel, and handle the movement throughout the tunnel

private:

	bool _ifFruitShown;
};
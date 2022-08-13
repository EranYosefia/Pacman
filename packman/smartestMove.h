#pragma once
#include "strategy.h"
#include "qitem.h"
#include <queue>

class SmartestMove : public Strategy {

public:
	
	virtual void moveStrategy(Board& b, Point& curPosition, Point& prevPosition,int& cd);

	int minDist(Board& b, std::vector<bool> visited, Point possibleNextLoc);
};
#pragma once
#include "board.h"
#include "definitions.h"

class Strategy {

public:

	virtual void moveStrategy(Board& b, Point& curPosition, Point& prevPosition, int& cd) = 0;

	Strategy() {}
};
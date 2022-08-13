#pragma once
#include "strategy.h"

class NoviceMove : public Strategy {

public:

	virtual void moveStrategy(Board& b, Point& curPosition, Point& prevPosition, int& c);
};
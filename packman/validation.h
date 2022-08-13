#pragma once
#include "definitions.h"

inline bool ifValidMove(char c) {

	return (c == UP || c == up || c == DOWN || c == down || c == LEFT || c == left || c == RIGHT || c == right || c == STAY || c == stay);
}

inline bool ifESC(char c) {

	return (c == ESC);
}

inline bool ifWon(int breadCrumbsCounter) {

	return (breadCrumbsCounter == 0);
}

inline bool ifLost(int lives) {

	return (lives == 0);
}

inline void determineDirections(char c, int& dirR, int& dirC) {

	if (c == RIGHT || c == right || c == 0) {
		dirR = 0;
		dirC = 1;
	}
	else if (c == LEFT || c == left || c == 1) {
		dirR = 0;
		dirC = -1;
	}
	else if (c == UP || c == up || c == 2) {
		dirR = -1;
		dirC = 0;
	}
	else if (c == DOWN || c == down || c == 3) {
		dirR = 1;
		dirC = 0;
	}
	else if (c == STAY || c == stay || c == 4) {
		dirR = 0;
		dirC = 0;
	}
}

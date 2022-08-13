#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#define NOMINMAX
#include <limits>
#include <filesystem>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct Point {
	
	int row;
	int colm;

	bool operator==(const Point& p) { return row == p.row && colm == p.colm; }
};

enum { ESC = 27 };

enum { BLUE = 9, RED = 4, GOLD = 6, WHITE = 7 };

#define UP 87  // Up Arrow 
#define DOWN 88 // Down Arrow 
#define LEFT 65  // Left Arrow 
#define RIGHT 68  // Right Arrow 
#define STAY 83

#define up 119  // Up Arrow 
#define down 120 // Down Arrow 
#define left 97  // Left Arrow
#define right 100  // Right Arrow 
#define stay 115

inline char drawNum5to9() {
	srand((unsigned int)time(NULL));
	int num = rand() % 5 + 5;
	return ('0' + num);
}
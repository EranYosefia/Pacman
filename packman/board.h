#pragma once
#include "validation.h"
#include <fstream>
#include <cmath>

class Board {

public:

	char getCellFromBoard(Point p) const;

	char getCellFromBreadVec(Point p) const;

	bool getVisited(Point p) const;
	
	int getRowsOfBoard() const;
	// Function returns the nubmer of rows
	int getColmsOfBoard() const;
	// Function returns the nubmer of colms
	Point getstatsPrintPosition() const;
	// Function returns the specific point on which will move to print the game stats
	
	std::vector<bool> getAllVisitedBoard() const;
	
	void setCellFromBoard(char value, Point p);

	void setCellFromBreadVec(Point p);

	void printStats(int& lives, int& score) const;

	void printBoard(bool ifColored) const;

	void printChanges(Point prevLoc,Point curLoc, bool ifColored);
	// Function Represnting the physical changes of an object movement on the board

	int initBreadVec();
	// Function initializing a Vector of breadcrumbs
	
	static void gotoxy(short x, short y);

	Point findFreePlace();
	//Function drawing a free and legal place for the fruit to pop-on on the board

	Board(const std::string& mapName);


private:

	std::vector<char> _board;
	std::vector<bool> _visited;
	std::vector <char> _breadCrumbsVec;

	int _rows;
	int _colms;

	Point _statsPrintPosition;
};
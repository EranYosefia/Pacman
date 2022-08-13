#include "menu.h"

void initOpMode(int argc, char** argv, int& operationMode);

int main(int argc, char** argv) {
	
	int operationMode = -1;
	initOpMode(argc, argv, operationMode);
	if (operationMode != -1) {
		Menu theMenu;
		theMenu.startMenu(operationMode);
	}
	return 0;
}
// operationMode:
// 0 for simple
// 1 for save
// 2 for load
// 3 for load silent
// -1 for wrong input

void initOpMode(int argc, char** argv, int& operationMode) {

	if (argc < 2)
		operationMode = 0;
	else if (strcmp(argv[1], "-save") == 0)
		operationMode = 1;
	else if (argc > 2 && strcmp(argv[1], "-load") == 0 && strcmp(argv[2], "-silent") == 0)
		operationMode = 3;
	else if (strcmp(argv[1], "-load") == 0)
		operationMode = 2;
	else
		std::cout << "Wrong input in command line";
}
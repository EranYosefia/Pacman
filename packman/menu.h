#pragma once
#include "game.h"

class Menu {
public:
		Menu(char c = 0) : _menuSelection(c) {}
		
		void startMenu(int operationMode);

		void LoadingMapsName(std::vector<std::string>& filenames);

		void gameLevelMenu(char& gameLevel);



		inline void print_menu() {

			std::cout << "(1) Start a new game" << std::endl << "(2) Start new game - Without colors" << std::endl << "(3) Upload specific map" << std::endl <<  "(8) Present instructions and keys" << std::endl << "(9) EXIT" << std::endl;
		}

		inline void print_instructions() {

			std::cout << "With Pacman you really get all of that. The idea here is that you are the hero in a maze and you have to eliminate all the enemies as fast as possible. You must do that as quickly as you can, otherwise you will lose the game and you definitely want to avoid such a thing as much as possible." << std::endl;
			std::cout << "The thing to keep in mind about Pacman is that you have to collect all the bubbles on the game board in order to complete the game." << std::endl;
			std::cout << "And while you do that you also need to figure out a way to avoid all those ghosts that are coming to get you.." << std::endl;
			std::cout << "The ability to play Pacman is really exciting because you are free to choose whatever route you want.And the Pacman online experience brings you so many different options all the time.You never get to have the same gameplay, even if the game is quite distinctand unique.It’s all about being creativeand having fun here, which is exactly what you need" << std::endl;
			std::cout << "LEFT........................................................ a or A" << std::endl;
			std::cout << "RIGHT....................................................... d or D" << std::endl;
			std::cout << "UP.......................................................... w or W" << std::endl;
			std::cout << "DOWN........................................................ x or X" << std::endl;
			std::cout << "STAY........................................................ s or S" << std::endl;
			std::cout << std::endl << "Press 5 to return to the menu" << std::endl;
		}
private:
	char _menuSelection;
};

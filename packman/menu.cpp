#include "menu.h"
namespace fs = std::filesystem;

void Menu::startMenu(int operationMode)
{
	std::vector<std::string> filenames;
	bool ifContinue = true;
	while (ifContinue) {

		if (operationMode == 2 || operationMode == 3) {
			_menuSelection = '1';
			ifContinue = false;
		}
		else {
			system("cls");
			print_menu();

			while (_menuSelection != '1' && _menuSelection != '2' && _menuSelection != '3' && _menuSelection != '8' && _menuSelection != '9')
				_menuSelection = _getch();
		}
		if (_menuSelection == '1' || _menuSelection == '2' || _menuSelection == '3') {

			char gameLevel = 0;
			bool ifColored = true;
			if (_menuSelection == '2')
				ifColored = false;
			LoadingMapsName(filenames);

			if (filenames.size() == 0) {
				system("cls");
				std::cout << "Map was not found" << std::endl;
				std::cout << "You will return to the menu in a few seconds";
				char r = _getch();
				Sleep(5000);
			}
			else {
				if (operationMode != 2 && operationMode != 3)
					gameLevelMenu(gameLevel);
				Game theGame(filenames, ifColored, gameLevel, operationMode);
				theGame.start();
			}
		}
		
		else if (_menuSelection == '8') {
			system("cls");
			print_instructions();
			_menuSelection = 0;
			while (_menuSelection != '5')
				_menuSelection = _getch();
		}
		else if (_menuSelection == '9') {
			system("cls");
			std::cout << "GoodBye...";
			ifContinue = false;
		}
		filenames.clear();
		_menuSelection = '0';
	}
}

void Menu::LoadingMapsName(std::vector<std::string>& filenames) {

	if (_menuSelection == '3') {
		system("cls");
		std::cout << "Enter a file name (Without extension .screen): ";
		std::string s;
		std::cin >> s;
		
		std::ifstream checkFile(s + ".screen");
		if (checkFile.good())
			filenames.push_back(s);
	}
	else // _menuSelection == '1' || _menuSelection == '2'
	{
		std::string ext(".screen");
		for (const auto& entry : fs::directory_iterator(".")) {

			if (entry.path().extension() == ext) {

				filenames.push_back(entry.path().stem().string());
			}
		}
	}
}

void Menu::gameLevelMenu(char& gameLevel) {

	system("cls");
	std::cout << "Enter game level" << std::endl << "1.Easy" << std::endl << "2.Normal" << std::endl << "3.Hard" << std::endl;
	while (gameLevel != '1' && gameLevel != '2' && gameLevel != '3')
		gameLevel = _getch();
}
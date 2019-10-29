#include <iostream> 
#include "GDWMastermind.h"
#include "assistance.h"


void AssistanceNecessary() {

	system("cls");

	std::cout << "Hello Welcome to Mastermind C++ Edition." << std::endl << std::endl;
	std::cout << "In order to control this game, you will use the arrow keys." << std::endl;
	std::cout << "In order to move up, press up, to move down, press down." << std::endl;
	std::cout << "To make a selection, press right, to go back press left." << std::endl << std::endl;
	std::cout << "When playing the game, the computer will select four colours from a selection of eight," << std::endl;
	std::cout << "there can be duplicates. It is up to you guess the correct colours in order, within 12 turns." << std::endl;
	std::cout << "When guessing, the computer will tell you if you got a colout correct, and it got the position correct." << std::endl << std::endl;
	std::cout << "Ready to go? " << std::endl;
	std::cout << "Press Enter To continue back to the main menu\n";

	std::cin.ignore();



	MainMenu();
}
#pragma once

struct secretCode
{
	std::string staticAnswer[4];
	std::string copyAnswer[4];
};

void checkPosition();

void checkColour();

void game(std::string a[4]);

void ButtonDownRight();

void ArrowSelection(bool  selectedOptionColour[8], std::string  guess[4], std::string  colourMenu[2][8]);

void CheckWin();

void ButtonDownLeft();

void PrintBoard();

void MoveArrowColour(int positiveNegative, int sizeOfArray, bool arrowPosition[], std::string a[2][8]);

void CheckLose();

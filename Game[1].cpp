#include <iostream>
#include "GDWMastermind.h"
#include "Game.h"
#include <conio.h> 
#include <windows.h> 

#define KEY_UP 72 
#define KEY_DOWN 80 
#define KEY_LEFT 75 
#define KEY_RIGHT 77 


secretCode colourCode;
HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
std::string colourMenu[2][8] = { {"->", ".",".",".",".",".",".","."},  { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange"} };
std::string guess[5] = { "*", "_","_","_", "" };
std::string prevGuess[12][4];
int colourIndex[8] = { 14, 12, 11, 10, 6, 16, 15, 6 };
int correctColour = 0;
int correctSpot = 0;
int guessCount = 0;
bool isContinue = false; // is for to check for if the arrow should be over the continue string and shouldn't allow for any up or down movement
bool selectedOptionColour[8] = { true, false, false, false, false, false, false, false };


void game(std::string copy[4]) 
{
	//Resets all of the variables to 0 if the palyer plays and then resets 
	guessCount = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			prevGuess[i][k] = "";
		}
	}

	//porting the secret code to this cpp
	for (int i = 0; i < 4; i++)
	{
		colourCode.staticAnswer[i] = copy[i];
		colourCode.copyAnswer[i] = copy[i];
	}
	system("cls");
	//menu items
	PrintBoard();
	ArrowSelection(selectedOptionColour, guess,colourMenu);

}
void ArrowSelection(bool  selectedOptionColour[8], std::string  guess[4], std::string  colourMenu[2][8])
{
	//menu selction thing
	bool running = true;
	int x = 0;
	while (running) //Moving the arrow 
	{
		x = 0;
		switch ((x = _getch()))
		{
		case KEY_UP:
			if (!(selectedOptionColour[0] == true) && !isContinue) //So the Arrow can't go off screen up  isContinue is to know if the Continue prompt is up and not to allow cursor mvment
			{
				MoveArrowColour(-1, 8, selectedOptionColour, colourMenu);
				PrintBoard();
			}
			break;
		case KEY_DOWN:
			if (!(selectedOptionColour[7] == true) && !isContinue) //so the Arrow cant go offscreen down and isContinue is to know if the Continue prompt is up and not to allow cursor mvment
			{
				MoveArrowColour(1, 8, selectedOptionColour, colourMenu);
				PrintBoard();
			}
			break;									
		case KEY_RIGHT:		
			if (guessCount == 12) //If the player loses
			{
				CheckLose();
			}
			ButtonDownRight();						
			PrintBoard();
			CheckWin();
			break;									
		case KEY_LEFT:								
			ButtonDownLeft();						
			PrintBoard();
			break;									
		default:
			break;
		}

	}
}
void CheckLose() 
{
	if (guessCount == 12)
	{
		system("cls");
		std::cout << "You Lose!\n";
		std::cout << "Press Enter to return to the main menu";

		std::cin.ignore();
		MainMenu();
	}
}
void CheckWin()
{
	if (correctColour == 4)
	{
		system("cls");
		std::cout << "Winner!!\n";
		std::cout << "Press Enter to return to the main menu";

		std::cin.ignore();
		MainMenu();
	}
}
void PrintBoard()
{
	SetConsoleTextAttribute(colour, 15);
	system("cls");
	std::cout << "Insert your guess\n";
	//prints the colours that the player has selected
	for (int i = 0; i < 5; i++)
	{
		std::cout << guess[i] << "\t";
	}
	std::cout << "\n";
	//prints out the colours menu for the plaer to select
	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(colour, 15);
		std::cout << colourMenu[0][i];
		SetConsoleTextAttribute(colour, colourIndex[i]);
		std::cout << colourMenu[1][i];
		std::cout << "\n";
	}
	SetConsoleTextAttribute(colour, 15);
	if (guessCount > 0)
	{
		std::cout << "There are " << correctColour << " In the correct spot and colour\n";
		std::cout << "There are " << correctSpot << " In the correct colour but wrong spot\n";
		std::cout << "Previous Guess(es) \n";
		for (int i = guessCount - 1; i >= 0; i--) //Prints out the Guesses in order of previous guess on the top
		{
			for (int k = 0; k < 4; k++)
			{
				std::cout << " " << prevGuess[i][k] << "\t";
			}
			std::cout << "\n";
		}
	}
}
void MoveArrowColour(int positiveNegative, int sizeOfArray, bool arrowPosition[], std::string option[2][8]) 
//moves the arrow up and down in the string and the bool arrays
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		if (arrowPosition[i])
		{
			for (int k = 0; k < sizeOfArray; k++)
			{
				option[0][k] = ".";
			}
			option[0][i + positiveNegative] = "->";
			std::cout << "\n";
			arrowPosition[i] = false;
			arrowPosition[i + positiveNegative] = true;
			break;
		}
	}
}
void ButtonDownRight()
{
	if (isContinue) //if the continue prompt is up then verify the code
	{
		correctColour = 0;
		correctSpot = 0;
		for (int i = 0; i < 4; i++)
		{
			prevGuess[guessCount][i] = guess[i];
		}
		for (int i = 0; i < 4; i++)
		{
			colourCode.copyAnswer[i] = colourCode.staticAnswer[i];
		}
		checkPosition();
		checkColour();
		guess[0] = "*";
		for (int i = 1; i < 4; i++)
		{
			guess[i] = "_";
		}
		guess[4] = "";
		isContinue = false;
		guessCount++;
	}
	else 
	{
		//loop to add the selected 
		for (int i = 0; i < 8; i++)
		{
			if (selectedOptionColour[i])
			{
				for (int k = 0; k < 4; k++)
				{
					if (guess[k] == "*")
					{
						if (k != 3)
						{
							guess[k + 1] = "*";
						}
						else
						{
							guess[k + 1] = "->Confirm?";
							isContinue = true;
							for (int k = 0; k < 8; k++)
							{
								colourMenu[0][k] = ".";
							}
						}
						guess[k] = colourMenu[1][i];
						break;
					}

				}
				break;
			}
		}
	}


}

void ButtonDownLeft()  //Left button press to remove the text and put a * and _
{
	for (int i = 0; i < 8; i++)
	{
		if (selectedOptionColour[i])
		{
			for (int k = 0; k < 4; k++)
			{
				if (guess[k] == "*")
				{
					if (k != 0)
					{
						guess[k - 1] = "*";
						guess[k] = "_";
					}
					break;
				}
				else if (k == 3)
				{
					guess[k] = "*";
					guess[k + 1] = "";
					isContinue = false; //continue prompt is no longer there
					MoveArrowColour(0, 8, selectedOptionColour, colourMenu); //draw the arrow back where it was last
				}
			}
			break;
		}
	}
}
void checkPosition() //checks if correct position and colour
{
	for (int i = 0; i < 4; i++)
	{
		if (guess[i] == colourCode.copyAnswer[i])
		{

			correctColour++;
			colourCode.copyAnswer[i] = "";
		}
	}
}

void checkColour() //checks if correct colour but wrong position
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (guess[i] == colourCode.copyAnswer[j])
			{
				correctSpot++;
				colourCode.copyAnswer[j] = "";
				break;
			}
		}
	}
	if (correctSpot > correctColour)
	{
		correctSpot -= correctColour;
	}
}


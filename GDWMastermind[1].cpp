#include <iostream> 
#include <conio.h> 
#include "GDWMastermind.h"
#include <time.h> 
#include <windows.h>
#include "Game.h"
#include "assistance.h"

std::string secretCode[4]; //Array with the Secret code 
std::string colours[8] = { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange" }; //All the colours 
std::string titleOptions[2][3] = { { "->", ".", "." }, {"Start", "Help", "Leave"} };
bool arrowPosition[3] = { true, false, false };
//Colours are Yellow, Red, Blue, Green, Brown, Black, Gray/White,  

#define KEY_UP 72 
#define KEY_DOWN 80 
#define KEY_LEFT 75 
#define KEY_RIGHT 77 

int main()
{
	MainMenu();
	return 0; //Ends the program By returning zero to main 
}

void MainMenu()
{
	RandomiseColours(); //Function to randomise the colours 
	RenderTitle(); //Renders the Ascii Art Title 
	ArrowKeyPress();
	std::cout << "end";
}

void ArrowKeyPress() //Checking if the key was pressed 
{
	bool running = true;
	int x = 0;
	while (running) //Moving the arrow 
	{
		x = 0;
		switch ((x = _getch())) 
		{
		case KEY_UP:
			if (!(arrowPosition[0] == true)) //So the Arrow can't go off screen up 
			{
				MoveArrowTitle(-1, 3, arrowPosition);
				RenderTitle();
			}
			break;
		case KEY_DOWN:
			if (!(arrowPosition[2] == true)) //so the Arrow cant go offscreen down 
			{
				MoveArrowTitle(1, 3, arrowPosition);
				RenderTitle();
			}
			break;
		case KEY_RIGHT:
			RightKeyPress();
			break;
		default:
			break;
		}
	}
}

void RightKeyPress()
{
	if (arrowPosition[0] == true)
	{
		StartGame();
	}
	else if (arrowPosition[1] == true)
	{
		AssistanceNecessary();
	}
	else if (arrowPosition[2] == true)
	{
		std::exit(0);
	}
}

void MoveArrowTitle(int positiveNegative, int sizeOfArray, bool arrowPosition[])
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		if (arrowPosition[i])
		{
			for (int k = 0; k < sizeOfArray; k++)
			{
				titleOptions[0][k] = ".";
			}
			titleOptions[0][i + positiveNegative] = "->";
			std::cout << "\n";
			arrowPosition[i] = false;
			arrowPosition[i + positiveNegative] = true;
			break;
		}
	}
}



void RenderTitle()
{
	system("cls");;
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string title[6] = { "  __  __              _               __  __  _             _ ",
		" |  \\/  |            | |             |  \\/  |(_)           | |",
		" | \\  / |  __ _  ___ | |_  ___  _ __ | \\  / | _  _ __    __| |",
		" | |\\/| | / _` |/ __|| __|/ _ \\| '__|| |\\/| || || '_ \\  / _` |",
		" | |  | || (_| |\\__ \\| |_|  __/| |   | |  | || || | | || (_| |",
		" |_|  |_| \\___| |___/ \\__|\\___||_|   |_|  |_||_||_| |_| \\____|" };


	for (int i = 0; i < 6; i++)
	{
		//changes colour for the title
		SetConsoleTextAttribute(colour, i + 1);
		std::cout << title[i] << "\n";
	}
	SetConsoleTextAttribute(colour, 15); //change colour to white for the rest of the text
	std::cout << "\n\n Select An option (Using the Arrow keys and press right arrow to select)" << "\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << titleOptions[0][i] << titleOptions[1][i];
		std::cout << "\n";

	}
}

void RandomiseColours()
{
	srand(time(0));
	for (int i = 0; i < 4; i++) //four being the length of the secret code 
	{
		int randomNum = std::rand() % 8; //Eight colours 
		secretCode[i] = colours[randomNum];
	}
}

void StartGame()
{
	game(secretCode);
}



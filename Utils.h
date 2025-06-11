#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdlib> 


	void gotoxy(int x, int y); //Moves the console cursor to the (x, y) coordinates.

	void ShowConsoleCursor(bool showFlag);//Stops the visibility of the console cursor.

	void clearInputBuffer(); // Clears all input from the console's input buffer.

	int getRandomNumber(int rangeStart, int rangeEnd); // Generates a random number from rangeStart to rangeEnd (Included).

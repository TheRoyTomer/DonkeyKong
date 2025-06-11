#include "Utils.h"

//Moves the console cursor to the (x, y) coordinates.
void gotoxy(int x, int y)
{
    std::cout.flush();
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

//Stops the visibility of the console cursor.
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void clearInputBuffer()
{
    // Clear any additional/leftover input from the buffer
    while (_kbhit())
    {
        _getch(); // Consume and discard all remaining input
    }
}

// Generates a random number from rangeStart to rangeEnd (Included).
int getRandomNumber(int RangeStart, int RangeEnd)
{
    return RangeStart + (rand() % (RangeEnd - RangeStart + 1));
}
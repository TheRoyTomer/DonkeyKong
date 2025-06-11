#pragma once
#include "Utils.h"
#include "Constans.h"
class Point
{
	static constexpr int EXPLODE_RADIUS = 2; // For % operator
	struct Direction { int x, y; };

	int x = 0; // Current x-coordinate.
	int y = 0; // Current y-coordinate.
	Direction curDir{ 0, 0 }; // Current movement direction.
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };  // Movement direction.
	char ch; // Char representing the point's symbol.

	// Draws a character at the current position
	void draw(char c) const 
	{
		gotoxy(x, y);
		std::cout << c;
	}

public:
	// Constructs a point.
	Point(int startX = 0, int startY = 0, char symbol = ' ') 
	{
		x = startX;
		y = startY;
		ch = symbol;
	}



	// Operator to check if two point's current location are in EXPLODE_RADIUS (2) units from each other
	bool operator%(const Point& other) const;

	// Operator to check if two point's current location are equal.
	bool operator==(const Point& other) const 
	{
		return this->x == other.x && this->y == other.y;
	}

	// Operator to check if two point's current location are not equal.
	bool operator!=(const Point& other) const
	{
		return this->x != other.x || this->y != other.y;
	}


	
	// Draws a character at the current position
	void draw() const
	{
		draw(ch);
	}

	// Erases the symbol.
	void erase() const
	{
		draw(' ');
	}

	// Moves the point in point's direction.
	void move()
	{
		x += curDir.x;
		y += curDir.y;
	}

	// Getters for position and direction.
	int getCurX() const
	{
		return x;
	}

	int getCurY() const
	{
		return y;
	}

	int getDirX() const
	{
		return curDir.x;
	}

	int getDirY() const
	{
		return curDir.y;
	}

	int getNextMoveX() const
	{
		return (x + curDir.x);
	}
	int getNextMoveY() const
	{
		return (y + curDir.y);
	}

	char getSymbol() const
	{
		return ch;
	}


	// Setters for position and direction.

	void setPointPosition(int newX, int newY)
	{
		x = newX;
		y = newY;
	}

	void decreaseCur_Y_ByOne()
	{
		y--;
	}

	void increaseCur_Y_ByOne()
	{
		y++;
	}

	void setDirByValues(int dirX, int dirY)
	{
		curDir.x = dirX;
		curDir.y = dirY;
	}

	void setDirByDirName(Constans::DirNames dirName)
	{
		curDir = directions[(int)(dirName)];
	}

	void resetDirX()
	{
		curDir.x = 0;
	}

	void resetDirY()
	{
		curDir.y = 0;
	}

	// Only for helping in explode animation.
	void setSymbol(char newChar)
	{
		ch = newChar;
	}
};

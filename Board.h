#pragma once
#include "Point.h"
#include "MenusAndPrompts.h"
#include <cstring>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;
class Board
{
private:
	// Data members for containing start posisions for objects while reading from the file.
	Point startMario;
	Point startPauline;
	Point startKong;
	Point startL;
	Point startHammer;
	std::vector<Point> startGhostsVEC;
	Point startPlus; // start for Plus (bonus section in project)

public:
	static constexpr char FLOOR_NORMAL = '='; // Standard floor.
	static constexpr char FLOOR_LEFT = '<'; // Floor directing left.
	static constexpr char FLOOR_RIGHT = '>'; // Floor directing right.
	static constexpr char LADDER = 'H'; // Ladder symbol
	static constexpr char KONG_SYMBOL = '&'; // Symbol representing Donkey Kong.
	static constexpr char PAULINE_SYMBOL = '$'; // Symbol representing Pauline.
	static constexpr char HUD_EDGE_SYMBOL = 'L'; // Symbol representing top ledt corner of HUD.
	static constexpr char BOUNDERIES_SYMBOL = 'Q'; // Symbol representing bounderies.


	char curBoard[Constans::MAX_Y][Constans::MAX_X + 1] = {};


public:

	// Function to clear the screen.
	void clearScreen()
	{
		system("CLS");
	}


	//Prototypes
	bool load(const std::string& fileName);

	void present();// Displays the board on the console.

	//Getters

	// Returns the character at a specific position on the board.
	char getCharFromBoard(int x, int y) const
	{
		return curBoard[y][x];
	}

	// Gets the floor type below a point (for barrel's movment).
	char getSignFloorBelow(const Point& p) const
	{
		return this->getCharFromBoard(p.getCurX(), p.getCurY() + 1);
	}

	Point GetStartMarioPos() const
	{
		return startMario;
	}

	Point GetStartPaulinePos() const
	{
		return startPauline;
	}

	Point GetStartDonkeyKongPos() const
	{
		return startKong;
	}

	Point GetStart_L_Pos() const
	{
		return startL;
	}

	Point GetStartPlusPos() const
	{
		return startPlus;
	}

	Point GetStartHammerPos() const
	{
		return startHammer;
	}

	std::vector<Point> Get_StartGhostsVEC_Pos() const
	{
		return startGhostsVEC;
	}



	// Sets new character at a specific position on the board.
	void setCharInBoard(int x, int y, char newCh)
	{
		curBoard[y][x] = newCh;
	}

	// Floor-related checks.
	
	// Checks and returns if the character is a floor.
	bool isFloor(const char ch) const
	{
		return (ch == FLOOR_NORMAL) || (ch == FLOOR_RIGHT) || (ch == FLOOR_LEFT);
	}

	// Checks and returns if a point is on a floor.
	bool isOnFloor(const Point& p) const
	{
		return this->isFloor(this->getCharFromBoard(p.getCurX(), p.getCurY()));
	}

	// Checks and returns if there's a floor below a point (we addressed the case where there is no floor in the bottom row of the screen).
	bool isFloorBelow(const Point& p) const
	{
		return (p.getCurY() + 1 == Constans::MAX_Y) ||(this->isFloor(this->getCharFromBoard(p.getCurX(), p.getCurY() + 1)));
	}

	// Checks and returns if there's a floor above a point.
	bool isFloorAbove(const Point& p) const
	{
		return this->isFloor(this->getCharFromBoard(p.getCurX(), p.getCurY() - 1));
	}

	// Checks and returns if the next move is onto a floor (We addressed the case where there is no floor in the bottom row of the screen).
	bool isNextMoveFloor(const Point& p) const
	{
		return (p.getNextMoveY() == Constans::MAX_Y) || (this->isFloor(this->getCharFromBoard(p.getNextMoveX(), p.getNextMoveY())));
	}

	// Checks and returns if the next move has a floor below.
	bool isNextMoveFloorBelow(const Point& p) const
	{
		return (p.getCurY() + 1 == Constans::MAX_Y) || (this->isFloor(this->getCharFromBoard(p.getNextMoveX(), p.getNextMoveY() + 1)));
	}

	// Ladder-related checks.
	
	// Checks and returns if the character is a ladder.
	bool isLadder(const char ch) const
	{
		return (ch == LADDER);
	}

	// Checks and returns if a point is on a ladder.
	bool isOnLadder(const Point& p) const
	{
		return this->isLadder(this->getCharFromBoard(p.getCurX(), p.getCurY()));
	}

	// Checks and returns if there's a ladder below a point.
	bool isLadderBelow(const Point& p) const
	{
		return this->isLadder(this->getCharFromBoard(p.getCurX(), p.getCurY() + 1));
	}

	// Checks and returns if there's a ladder two characters below a point.
	bool isLadderTwoCharsBelow(const Point& p) const
	{
		return (p.getCurY() < Constans::MAX_Y - 2) && (this->isLadder(this->getCharFromBoard(p.getCurX(), p.getCurY() + 2)));
	}

	
	// Boundary checks.

	// Checks and returns if a point's X coordinate is within boundaries.
	bool checkIfIn_X_Boundaries(const Point& p) const
	{
		return (p.getCurX() >= 0) && (p.getCurX() <= Constans::MAX_X - 1);
	}

	// Checks and returns if a point's Y coordinate is within boundaries.
	bool checkIfIn_Y_Boundaries(const Point& p) const
	{
		return  (p.getCurY() >= 0) && (p.getCurY() < Constans::MAX_Y - 1) || ((p.getCurY() == Constans::MAX_Y - 1) && !isOnFloor(p));
	}

	// Checks and returns if an explosion can be drawn at a point.
	bool canDrawExplode(const Point& p) const
	{
		return checkIfIn_X_Boundaries(p) && checkIfIn_Y_Boundaries(p) && !isOnFloor(p);
	}
};


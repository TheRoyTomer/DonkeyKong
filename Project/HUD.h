#pragma once
#include <string>
#include "Point.h"
#include "SilentState.h"
class HUD
{
	// The HUD is split to two columns
	static constexpr int FIRST_COL_DISPLAYS_LENGTH = 11;
	static constexpr int SECOND_COL_DISPLAYS_LENGTH = 8;
	static constexpr char SEPERATOR = '|';
	static constexpr int X_VALUE_SEPERATOR_FROM_START_X = 11;
	static constexpr int START_X_SECOND_COL_DISPLAYS_FROM_START_X = X_VALUE_SEPERATOR_FROM_START_X + 1;


	static constexpr int HUD_Height = 3;
	static constexpr int HUD_Width = 20;
	static constexpr const char* LIFE_SYMBOL = "<3";
	static constexpr const char* NO_HAMMER_PROMPT = "No Hammer";
	static constexpr const char* HAMMER_PROMPT = "Hammer Time";
	static constexpr const char* PLUS_PROMPT = "Immortal";

	Point topLeftCorner;
	// Start point of every HUD part
	Point startPosLifeDisplay;
	Point startPosScoreDisplay;
	Point startPosHammerDisplay;
	Point startPosLoopsDisplay;
	Point startPos_P_Display;
	Point startPos_PLUS_Display;


public:
	HUD(const Point& _topLeftCorner = Point());



	void clearDIsplay(const Point& start, int displayLength);
	void displayHUD(int curLife, int score, bool isHoldingHammer, int loopsCounter, bool is_P_Pressed, bool _isPlusCativated, int immortalLoopsRemaining = 0);
	void displayLife(int curLife);
	void displayScore(int score);
	void displayHammer(bool isHoldingHammer);
	void display_P_Pressed(bool is_P_Pressed);
	void displayLoops(int loopsCounter);
	void displayPlusState(bool _isPlusCativated , int immortalLoopsRemaining = 0);
	void displaySeperators();
	//Updates the HUD after strike.
	void displayHUD_AfterStrike(int curLife);
};


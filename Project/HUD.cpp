#include "HUD.h"

HUD::HUD(const Point& _topLeftCorner) : topLeftCorner(_topLeftCorner)
{
	startPosLifeDisplay = topLeftCorner;
	startPosScoreDisplay = Point(topLeftCorner.getCurX(), topLeftCorner.getCurY() + 1);
	startPosHammerDisplay = Point(topLeftCorner.getCurX(), topLeftCorner.getCurY() + 2);
	startPos_PLUS_Display = Point(topLeftCorner.getCurX() + START_X_SECOND_COL_DISPLAYS_FROM_START_X, topLeftCorner.getCurY());
	startPosLoopsDisplay = Point(topLeftCorner.getCurX() + START_X_SECOND_COL_DISPLAYS_FROM_START_X, topLeftCorner.getCurY() + 1);
	startPos_P_Display = Point(topLeftCorner.getCurX() + START_X_SECOND_COL_DISPLAYS_FROM_START_X, topLeftCorner.getCurY() + 2);
}

void HUD::clearDIsplay(const Point& start, int displayLength)
{
	if (!SilentState::getSilentMode())
	{
		gotoxy(start.getCurX(), start.getCurY());
		std::cout << std::string(displayLength, ' '); // Overwrite the row with spaces
	}
}

// Displaying the entire HUD at once
void HUD::displayHUD(int curLife, int score, bool isHoldingHammer, int loopsCounter, bool is_P_Pressed, bool _isPlusCativated, int immortalLoopsRemaining)
{
	if (!SilentState::getSilentMode())
	{
		displayLife(curLife);
		displayScore(score);
		displayHammer(isHoldingHammer);
		displayPlusState(_isPlusCativated, immortalLoopsRemaining);
		display_P_Pressed(is_P_Pressed);
		displayLoops(loopsCounter);
		displaySeperators();
	}
}

// Display the remaining lives on HUD.
void HUD::displayLife(int curLife)
{
	if (!SilentState::getSilentMode())
	{
		clearDIsplay(startPosLifeDisplay, FIRST_COL_DISPLAYS_LENGTH);
		gotoxy(startPosLifeDisplay.getCurX(), startPosLifeDisplay.getCurY());
		for (int i = 0; i < curLife; ++i)
		{
			std::cout << LIFE_SYMBOL;
			if (i != curLife - 1)
			{
				std::cout << " ";
			}
		}
	}
}
// Display the score on HUD.
void HUD::displayScore(int score)
{
	if (!SilentState::getSilentMode())
	{
		clearDIsplay(startPosScoreDisplay, FIRST_COL_DISPLAYS_LENGTH);
		gotoxy(startPosScoreDisplay.getCurX(), startPosScoreDisplay.getCurY());
		std::cout << "Score: " << score;
	}
}

// Display holding hammer state on HUD.
void HUD::displayHammer(bool isHoldingHammer)
{
	if (!SilentState::getSilentMode())
	{
		clearDIsplay(startPosHammerDisplay, FIRST_COL_DISPLAYS_LENGTH);
		gotoxy(startPosHammerDisplay.getCurX(), startPosHammerDisplay.getCurY());
		if (isHoldingHammer)
		{
			std::cout << HAMMER_PROMPT;
		}
		else
		{
			std::cout << NO_HAMMER_PROMPT;
		}
	}
}

// Display if p pressed lives on HUD.
void HUD::display_P_Pressed(bool is_P_Pressed)
{
	if (!SilentState::getSilentMode())
	{
		gotoxy(startPos_P_Display.getCurX(), startPos_P_Display.getCurY());

		if (is_P_Pressed)
		{
			std::cout << Constans::HAMMER_SYMBOL;
		}
		else
		{
			std::cout << ' ';
		}
	}
}

// Display loop counter lives on HUD.
void HUD::displayLoops(int loopsCounter)
{
	if (!SilentState::getSilentMode())
	{
		clearDIsplay(startPosLoopsDisplay, SECOND_COL_DISPLAYS_LENGTH);
		gotoxy(startPosLoopsDisplay.getCurX(), startPosLoopsDisplay.getCurY());
		std::cout << loopsCounter;
	}
}

void HUD::displayHUD_AfterStrike(int curLife)
{
	if (!SilentState::getSilentMode())
	{
		displayLife(curLife);
		displayHammer(false);
	}
}

//Displaying plus state in unique way.
void HUD::displayPlusState(bool _isPlusCativated, int immortalLoopsRemaining)
{
	if (!SilentState::getSilentMode())
	{
		clearDIsplay(startPos_PLUS_Display, SECOND_COL_DISPLAYS_LENGTH);
		if (_isPlusCativated && immortalLoopsRemaining != 0)
		{
			gotoxy(startPos_PLUS_Display.getCurX(), startPos_PLUS_Display.getCurY());
			if (immortalLoopsRemaining < 10 && immortalLoopsRemaining % 2 != 0)
			{
				std::cout << "   " << immortalLoopsRemaining;
			}
			else
			{
				std::cout << PLUS_PROMPT;
			}
		}
	}
}

// Add the seperators between the columns.
void HUD::displaySeperators()
{
	if (!SilentState::getSilentMode())
	{
		for (int i = 0; i < HUD_Height; i++)
		{
			gotoxy(topLeftCorner.getCurX() + X_VALUE_SEPERATOR_FROM_START_X, topLeftCorner.getCurY() + i);
			std::cout << SEPERATOR;
		}
	}
}


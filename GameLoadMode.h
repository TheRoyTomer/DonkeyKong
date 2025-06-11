#pragma once
#include "Game.h"
class GameLoadMode : public Game
{
	static constexpr int START_DISPLAY_ERROR_X = 15;
	static constexpr int START_DISPLAY_ERROR_SCREEN_AND_ITERATION_Y = 16;
	static constexpr int START_DISPLAY_ERROR_REASON_Y = 17;
	static constexpr int SLEEP_DURING_MOVING_LOAD_NOTSILENT = 50; // Delay between mario and barrels movement (in milliseconds) in load mode without silent.

	bool isLoad = true;

public:
	GameLoadMode( bool _isSilent = false);

	//Runs entire game session in load mode.
	void RunGame() override;

	// Function that handle keys from file, and checks few errors in comparing with result file. returns true if there is a mismatch between the file and the game.
	bool handleInput(size_t iteration, Results& currRes, Steps& currStep, std::string fileName) override;

	//Function that handles results update after strike.
	bool handleFilesAfterStrike(size_t iteration, Results& currRes, std::string fileName) override;

	//Function that handles end of level, compare to result file and return false for mismatch.
	bool handleEndOfLevel(Steps& currSteps, Results& currRes, int levelScore, std::string fileName, size_t iteration) override;

	void handleStartOfLevel(Steps& currSteps, Results& currRes, std::string fileName) override;

	//Handle and deal with invalid file.
	bool handleInvalidFile( std::string fileName) override;

	//Handle displaying error prompt with the reason for error.
	void handleResultErrorPrompt(std::string error, size_t iteration, std::string fileName);

	//Handle displaying prompt that single level matched with his result file.
	void handleResultSuccessPrompt();

	//Handle displaying prompt if all the levels are matched with their results file.
	void handleAllLevelsComparationSuccessPrompt();

	//Handle sleep in load mode.
	void handleSleep() override
	{
		if (!SilentState::getSilentMode())
		{
			Sleep(SLEEP_DURING_MOVING_LOAD_NOTSILENT);
		}
	}

};


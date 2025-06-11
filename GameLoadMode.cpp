#include "GameLoadMode.h"

GameLoadMode::GameLoadMode(bool _isSilent)
{
	if (_isSilent)
	{
		SilentState::setToSilentMode();
	}
}

//Runs entire game session in load mode.
void GameLoadMode::RunGame()
{
	getAllBoardFileNames(LevelNamesVEC);
	bool isValidFile;
	int numEnemyKilled, numStrikes;
	ShowConsoleCursor(false); // Hides the console cursor.
	
	// Runs on every level between start level to the end of the vector.
	// If player's remaining lives equals 0, stop this session.
	for (int i = 0; i < LevelNamesVEC.size(); i++)
	{
		isValidFile = true;
		numEnemyKilled = 0;
		numStrikes = 0;

		// Function runs single level and returns If the user chose to end game session.
		if (!RunLevel(LevelNamesVEC[i], &isValidFile, &numEnemyKilled, &numStrikes))
		{
			return;
		}
		else if (!SilentState::getSilentMode && i + 1 == LevelNamesVEC.size())
		{
			handleResultSuccessPrompt();
		}
	}
	handleAllLevelsComparationSuccessPrompt();
}

void GameLoadMode::handleStartOfLevel(Steps& currSteps, Results& currRes, std::string fileName)
{
	std::string fileName_prefix = fileName.substr(0, fileName.find_last_of('.'));
	std::string stepsFileName = fileName_prefix + ".steps";
	std::string resultsFileName = fileName_prefix + ".result";

	currSteps = Steps::loadSteps(stepsFileName);
	srand(currSteps.getRandomSeed());
	currRes = Results::loadResults(resultsFileName);
}

bool GameLoadMode::handleInvalidFile( std::string fileName)
{
	handleResultErrorPrompt("File is invalid!", 0, fileName);
	return false;
}

// Function that handle keys from file, and checks few errors in comparing with result file. returns true if there is a mismatch between the file and the game.
bool GameLoadMode::handleInput(size_t iteration, Results& currRes, Steps& currStep, std::string fileName)
{
	//Checks if results vec ends with finish event. the check is occured just in the first iteration.
	if (iteration == 0 && !currRes.isLastEventIsFinished())
	{
		handleResultErrorPrompt("Results file doesn't end with finish event!", iteration, fileName);
		return true;
	}
	if (currRes.IsPassedNextStrikeIteration(iteration))
	{
		handleResultErrorPrompt("Results file have a strike event that didn't happen!", iteration, fileName);
		return true;
	}
	if (currRes.isFinishedBy(iteration))
	{
		handleResultErrorPrompt("Results file reached finish while game hadn't!", iteration, fileName);
		return true;
	}
	if (currStep.isNextStepOnIteration(iteration))
	{
		std::string temp = currStep.popStep();
		if (!temp.empty())
		{
			if (temp[0] == Constans::HAMMER_SYMBOL)
			{
				is_P_Pressed = true;
			}
			else
			{
				player.keyPressed(temp[0]);
				if (temp.size() > 1)
				{
					is_P_Pressed = true;
				}
			}
		}
	}
	return false;
}

//Function that handles results update after strike.
bool GameLoadMode::handleFilesAfterStrike(size_t iteration, Results& currRes, std::string fileName)
{
	if(currRes.popResult() != std::pair{ iteration, Results::Strike })
	{
		handleResultErrorPrompt("Results file doesn't match strike event!", iteration, fileName);
		return false;
	}
	return true;
}

//Function that handles end of level, compare to result file and return false for mismatch.
bool GameLoadMode::handleEndOfLevel(Steps& currSteps, Results& currRes, int levelScore, std::string fileName, size_t iteration)
{
	if (currRes.CompareFinishIterations(iteration))
	{
		if (currRes.getScore() == levelScore)
		{
			totalScore += levelScore;
			return true;
		}
		handleResultErrorPrompt("Score in results file doesn't match session score!", iteration, fileName);
		return false;

	}
	else
	{
		handleResultErrorPrompt("Results file doesn't match finished event!", iteration, fileName);
		return false;
	}

}

//Handle displaying error prompt with the reason for error.
void GameLoadMode::handleResultErrorPrompt(std::string error, size_t iteration, std::string fileName)
{
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::ResultErrorPromptScreen);
	gotoxy(START_DISPLAY_ERROR_X, START_DISPLAY_ERROR_SCREEN_AND_ITERATION_Y);
    std::cout << "Screen " << fileName << ": " << "Iteration: " << iteration;
	gotoxy(START_DISPLAY_ERROR_X, START_DISPLAY_ERROR_REASON_Y);
	std::cout << error;
	Sleep(5000);
}

//Handle displaying prompt that single level matched with his result file.
void GameLoadMode::handleResultSuccessPrompt()
{
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::ResultSuccessPromptScreen);
	_getch();
}

//Handle displaying prompt if all the levels are matched with their results file.
void GameLoadMode::handleAllLevelsComparationSuccessPrompt()
{
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::AllLevelsComparationSuccessPromptScreen);
	_getch();
}

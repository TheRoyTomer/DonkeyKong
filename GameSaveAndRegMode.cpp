#include "GameSaveAndRegMode.h"

// Runs the entire game, including the main menu and levels.
void GameSaveAndRegMode::RunGame()
{
	getAllBoardFileNames(LevelNamesVEC);
	bool finishProgram = false;
	bool DoreturnToMainMenu;
	bool isValidFile;
	int  numEnemyKilled, numStrikes;
	int startLevel = 0;
	ShowConsoleCursor(false); // Hides the console cursor.
	// While the user don't want to finish the game.
	while (!finishProgram)
	{
		player.setToStartLife();
		startLevel = 0;
		DoreturnToMainMenu = false;
		totalScore = 0; // Initial the total score.

		finishProgram = handleMainMenuScreen(&startLevel);// Display the main menu, returns true if the game should be stoped.

		if (finishProgram)
		{
			return;
		}
		else
		{
			// Runs on every level between start level to the end of the vector.
			// If player's remaining lives equals 0, stop this session.
			for (int i = startLevel; i < LevelNamesVEC.size() && player.getCurLife() > 0; i++)
			{
				isValidFile = true;
				numEnemyKilled = 0;

				numStrikes = 0;

				// Function runs single level and returns If the user chose to end game session.
				if (!RunLevel(LevelNamesVEC[i], &isValidFile, &numEnemyKilled, &numStrikes))
				{
					DoreturnToMainMenu = true;
					break;
				}
				// If the user still has lives and the file is valid - add the score he achieved to total score, and present level complited screen. 
				if (player.getCurLife() > 0 && isValidFile)
				{
					totalScore += HandlelevelCompletedPromptAndScoreCalc(numStrikes, numEnemyKilled);
					// Prevent negtive score.
					if (totalScore < 0)
					{
						totalScore = 0;
					}
				}
			}
			if (!DoreturnToMainMenu)
			{
				// If the user still has lives, present winning screen and the score.
				if (player.getCurLife() > 0)
				{
					presentPrompts.printWinningPrompt(totalScore);
				}
				else
				{
					//The user has no lives left, display the game over screen.
					presentPrompts.printPrompts(MenusAndPrompts::Prompts::GameOverPromptScreen);
				}
			}
		}
	}
}

//Handle start of level in save or regular mode and implement random seed.
void GameSaveAndRegMode::handleStartOfLevel(Steps& currSteps, Results& currRes, std::string fileName)
{
	long randomSeed = static_cast<unsigned int>(time(0));
	srand(randomSeed); // Initialize the random seed
	currSteps.setRandomSeed(randomSeed); //Insert the ransom seed to Steps object.
}

bool GameSaveAndRegMode::handleInvalidFile( std::string fileName)
{
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::InvalidFilePromptScreen);
	return true;
}


// Function that gets pressed keys and handle them. returns true if we need to return to main menu.
bool GameSaveAndRegMode::handleInput(size_t iteration, Results& currRes, Steps& currStep, std::string fileName)
{
	char key = ' ', key2 = ' ';
	// Gets the single input from the user unless the firs input is direction and the seconed is 'p'.
	// If one of the inputs is 'p'- cange the flag is_p_pressed to true.
	if (_kbhit()) // Check for key press.
	{
		key = std::tolower(_getch());
		// If the player pressed escape, pause the game.
		if (key == ESC)
		{
			// Function that handle paused game. If it return true, stop the game and return to main menu.
			if (handlePausePrompt())
			{
				return true;
			}
			else
			{
				// Redraw the board after pause.
				myBoard.present();
				hud.displayHUD(player.getCurLife(), totalScore, player.getIsHoldingHammer(), counterGameLoops, is_P_Pressed, isPlusActivated, immortalCounter);
			}
		}
		else if (std::tolower(key) == Constans::HAMMER_SYMBOL)
		{
			is_P_Pressed = true;
		}
		else if (player.validKey(key))
		{
			player.keyPressed(key); // Process Mario's movement.
			if (std::tolower(key) != Constans::HAMMER_SYMBOL && _kbhit())
			{
				key2 = _getch();
				if (std::tolower(key2) == Constans::HAMMER_SYMBOL)
				{
					is_P_Pressed = true;
				}
			}
		}
		clearInputBuffer();
		if (isSaveMode && (player.validKey(key) || key == Constans::HAMMER_SYMBOL))
		{
			std::string temp;
			temp.push_back(key);

			if (key != Constans::HAMMER_SYMBOL && key2 == Constans::HAMMER_SYMBOL)
			{
				temp.push_back(key2);
			}
			currStep.addStep(iteration, temp);
		}
	}
	return false;
}

//Function that handles results update after strike.
bool GameSaveAndRegMode::handleFilesAfterStrike(size_t iteration, Results& currRes, std::string fileName)
{
	currRes.addResult(iteration, Results::Strike);
	return true;
}

//Handle end of level. if the game ended because game over or mario succsseded, and return true. else, return false to stop the session.
bool GameSaveAndRegMode::handleEndOfLevel(Steps& currSteps, Results& currRes, int levelScore, std::string fileName, size_t iteration)
{
	if ((isWonLevel(player) || isGameOver(player)))
	{
		if (isSaveMode)
		{
			currRes.addResult(counterGameLoops, Results::Finished);
			currRes.setScore(levelScore);
			std::string fileName_prefix = fileName.substr(0, fileName.find_last_of('.'));
			std::string stepsFileName = fileName_prefix + ".steps";
			std::string resultsFileName = fileName_prefix + ".result";
			currSteps.saveSteps(stepsFileName);
			currRes.saveResults(resultsFileName);
		}
		return true;
	}
	return false;
}


// Displays the main menu and processes user input.
bool GameSaveAndRegMode::handleMainMenuScreen(int* levelToStart)
{
	char key;
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::MainMenuScreen); // Display the menu.
	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case '1': // Start game from start
				// If there are no files, display no files screen and return true to finish the game.
				if (LevelNamesVEC.empty())
				{
					presentPrompts.printPrompts(MenusAndPrompts::Prompts::NoFilesPromptScreen);
					*levelToStart = -1;
					return true;
				}
				else
				{
					// Sets level to start to 0, return false to continue the game.
					*levelToStart = 0;
					return false;
				}


			case '2':// Starts the game from the file that the user selected.
				// If there are no files, display no files screen and return true to finish the game.
				if (LevelNamesVEC.empty())
				{
					presentPrompts.printPrompts(MenusAndPrompts::Prompts::NoFilesPromptScreen);
					*levelToStart = -1;
					return true;
				}
				else
				{
					// Gets the level to start from handle_Start_By_Select_File_Screen function.
					*levelToStart = handle_Start_By_Select_File_Screen();
					// level to start equals -1, marks that the player wants to return to main menu.
					if (*levelToStart == -1)
					{
						presentPrompts.printPrompts(MenusAndPrompts::Prompts::MainMenuScreen);
						break;
					}
					else
					{
						return false;
					}
				}

			case '8': // Show instructions.
				handleInstructions_And_KeysScreen();
				presentPrompts.printPrompts(MenusAndPrompts::Prompts::MainMenuScreen);  // When returning from instructions menu, present main menu.
				break;

			case '9': // Exit game.
				*levelToStart = -1;
				// Return true to finish the game.
				return true;
			}
		}

	}

}

// Displays instructions and keybindings.
void GameSaveAndRegMode::handleInstructions_And_KeysScreen()
{
	char key = ' ';
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::Instructions_And_KeysPromptScreen); // Display instructions.
	while (key != ESC)
	{
		if (_kbhit())
		{
			key = _getch();
		}
	}
}

// Handles the pause menu and its options.
bool GameSaveAndRegMode::handlePausePrompt()
{
	char key;
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::PausedGamePromptScreen); // Display pause menu
	key = std::tolower(_getch());
	while (key != LOWER_R && key != ESC)
	{
		key = std::tolower(_getch());
	}
	// Return true if "R" is pressed (means the player wants to return to main menu), otherwise false.
	if (key == LOWER_R)
	{
		return true;
	}
	else
	{
		return false;
	}

}


int GameSaveAndRegMode::handle_Start_By_Select_File_Screen()
{
	char key;
	int startFileDisplay;
	// If there are more then 9 files, display only the last 9.
	if (LevelNamesVEC.size() <= 9)
	{
		startFileDisplay = 0;
	}
	else
	{
		startFileDisplay = LevelNamesVEC.size() - 9;
	}
	presentPrompts.printPrompts(MenusAndPrompts::Prompts::startBySelectFileScreen);
	gotoxy(START_X_FILE_LIST_NAMES, START_Y_FILE_LIST_NAMES);
	std::cout << '[' << 0 << "]: Return to main menu" << std::endl;
	for (int i = 0; i < LevelNamesVEC.size() && i < 9; i++)
	{
		gotoxy(START_X_FILE_LIST_NAMES, START_Y_FILE_LIST_NAMES + i + 1);
		std::cout << '[' << i + 1 << "]:" << LevelNamesVEC[startFileDisplay + i] << std::endl;
	}
	key = _getch();
	// If the user selected '0', return -1 to mark that the user wants to return to main menu.
	if (key == '0')
	{
		return -1;
	}
	// Continue receive input until the user gives valid input.
	while (key < '0' || key > '9' || startFileDisplay + (key - '0') - 1 >= LevelNamesVEC.size())
	{
		key = _getch();
		// If the user selected '0', return -1 to mark that the user wants to return to main menu.
		if (key == '0')
		{
			return -1;
		}

	}
	// Return the level the user wants to start with.
	return  startFileDisplay + (key - '0') - 1;

}



int GameSaveAndRegMode::HandlelevelCompletedPromptAndScoreCalc(int numStrikes, int numEnemyKilled)
{
	// Score arr represents in each cell how many points player achieved in each score catagory:
// ScoreArr[0]: speed bonus, ScoreArr[1]: enemy kill bonus, ScoreArr[2]: strikes Penalty, ScoreArr[3]: no damage bonus, ScoreArr[4]: collecting + bonus  ScoreArr[5]: total score for this level.
	int scoreArr[6];
	calcScore(numStrikes, numEnemyKilled, scoreArr);
	presentPrompts.printLevelCompletedPrompt(numStrikes, numEnemyKilled, counterGameLoops, isPlusAlreadyActivated, scoreArr);
	return scoreArr[5];
}




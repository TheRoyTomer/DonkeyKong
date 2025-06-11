#pragma once
#include "Game.h"
#include <ctime> 
class GameSaveAndRegMode : public Game
{
	bool isSaveMode = false;
	static constexpr int ESC = 27; // Key code for the Escape key.
	static constexpr int LOWER_R = 114; // Key code for the 'R' key.
	static constexpr int SLEEP_DURING_MOVING_REG_AND_SAVE = 250; // Delay between mario and barrels movement (in milliseconds) in regular or save mode.

	static constexpr int START_X_FILE_LIST_NAMES = 16; // Start X loction in the file's names screen.
	static constexpr int START_Y_FILE_LIST_NAMES = 7; // Start Y loction in the file's names screen.
public:
	//GameSaveAndRegMode ctor
	GameSaveAndRegMode (bool _isSaveMode) : isSaveMode(_isSaveMode) {}

	void RunGame() override;


	// Function that gets pressed keys and handle them. returns true if we need to return to main menu.
	 bool handleInput(size_t iteration, Results& currRes, Steps& currStep, std::string fileName) override;

	//Function that handles results update after strike.
	 bool handleFilesAfterStrike(size_t iteration, Results& currRes, std::string fileName) override;

	 //Handle start of level in save or regular mode and implement random seed.
	 void handleStartOfLevel(Steps& currSteps, Results& currRes, std::string fileName) override;

	 //Handle end of level. if the game ended because game over or mario succsseded, and return true. else, return false to stop the session.
	 bool handleEndOfLevel(Steps& currSteps, Results& currRes, int levelScore, std::string fileName, size_t iteration) override;

	 bool handleInvalidFile( std::string fileName) override;

	 bool handleMainMenuScreen(int* levelToStart); // Displays the main menu and handles user input.
	 void handleInstructions_And_KeysScreen(); // Displays instructions and keybindings.
	 bool handlePausePrompt(); // Handles the pause menu and its options.
	 int handle_Start_By_Select_File_Screen();
	 int HandlelevelCompletedPromptAndScoreCalc(int numStrikes, int numEnemyKilled);

	 void handleSleep() override
	 {
		 Sleep(SLEEP_DURING_MOVING_REG_AND_SAVE);
	 }


};


#pragma once
#include "Utils.h"
#include "Constans.h"
#include "HUD.h"


class MenusAndPrompts
{
public:
	//enum for identifying which prompt to print. it's in public in order to use that as well in Game, where the print prompts function is used.
	enum class Prompts {MainMenuScreen = 1, WinningPromptScreen, GameOverPromptScreen, Instructions_And_KeysPromptScreen, PausedGamePromptScreen,
		                InvalidFilePromptScreen, NoFilesPromptScreen, LevelCompletedPromptScreen, startBySelectFileScreen, ResultErrorPromptScreen,
		                ResultSuccessPromptScreen, AllLevelsComparationSuccessPromptScreen};
private:
	static constexpr int SLEEP_IN_PROMPTS = 5000; // Delay after prompts.

	static constexpr int START_DISPLAY_SCORE_DATA_X = 21; // X value to start printing score explanation in levelCompletedPrompt.
	static constexpr int START_DISPLAY_SCORE_DATA_Y = 16; // Y value to start printing score explanation in levelCompletedPrompt.
	static constexpr int START_FINAL_DISPLAY_SCORE_DATA_X = 19; // X value to start printing final score in WinningPrompt.
	static constexpr int START_FINAL_DISPLAY_SCORE_DATA_Y = 17; // Y value to start printing final score in WinningPrompt.




	// Main menu display content.
	static const char MainMenu[Constans::MAX_Y][Constans::MAX_X + 1];
	// Winning screen display content.
	static const char WinningPrompt[Constans::MAX_Y][Constans::MAX_X + 1];
	// Game over screen display content.
	static const char GameOverPrompt[Constans::MAX_Y][Constans::MAX_X + 1];
	// Instructions and keys display content.
	static const char Instructions_And_KeysPrompt[Constans::MAX_Y][Constans::MAX_X + 1];
	// Pause screen display content.
	static const char PausedGamePrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	// Invalid file screen display content.
	static const char InvalidFilePrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	// No files screen display content.
	static const char NoFilesPrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	// Level completed screen display content.
	static const char LevelCompletedPrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	// Select file to start from screen display content.
	static const char startBySelectFile[Constans::MAX_Y][Constans::MAX_X + 1];

	// Screen to display error between game session and result file
	static const char ResultErrorPrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	//screen to display that level and his result file are the same.
	static const char ResultSuccessPrompt[Constans::MAX_Y][Constans::MAX_X + 1];

	//screen to display that all levels and result file are the same.
	static const char AllLevelsComparationSuccessPrompt[Constans::MAX_Y][Constans::MAX_X + 1];
	

	public:
		//Prototypes
		void printPrompts(Prompts srn);
		void printLevelCompletedPrompt(int numStrikes, int numEnemyKilled, int levelLoopsCounter, bool isPlusPicked, int* scoreArr);
		void printWinningPrompt(int finalScore);	
};


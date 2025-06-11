#include "MenusAndPrompts.h"

const char MenusAndPrompts::MainMenu[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//	          10         20        30       40        50        60        70        80
	  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ",//0
		"                                                                               ",//1
		"                                                                               ",//2
		"                                                                               ",//3
		"                                                                               ",//4
		"                                                                               ",//5
		"            Welcome to Mor Greenberg and Roy Tomer Donkey Kong game!!          ",//6
		"                                                                               ",//7
		"                   [1]: Start a new game                                       ",//8
		"                   [2]: Start by selecting level                               ",//9
		"                   [8]: Present instructions and keys  (for begginers....)     ",//10
		"                   [9]: EXIT                                                   ",//11
		"                                                                               ",//12
		"                                                                               ",//13
		"                                                                               ",//14
		"                                                                               ",//15
		"                                                                               ",//16
		"                                                                               ",//17
		"                                                                               ",//18
		"                                                                               ",//19
		"                                                                               ",//20
		"                                                                               ",//21
		"                                                                               ",//22
		"                                                                               ",//23
		"                                                                               ",//24
};

// Winning screen display content.
const char MenusAndPrompts::WinningPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                                                                                ", // 3
	"                                                                                ", // 4
	"                                                                                ", // 5
	"                                                                                ", // 6
	"                                                                                ", // 7
	"                                                                                ", // 8
	"                    WWW        WWW     IIIII    NNN   NNN                       ", // 9
	"                    WWW        WWW      III     NNNN  NNN                       ", // 10
	"                    WWW   WW   WWW      III     NNNNN NNN                       ", // 11
	"                    WWW  WWWW  WWW      III     NNNNNNNNN                       ", // 12
	"                     WWWWWWWWWWWWW     IIIII    NNN   NNN                       ", // 13
	"                                                                                ", // 14
	"                           YOU ARE THE CHAMPION!                                ", // 15
	"                                                                                ", // 16
	"                                                                                ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                ", // 23
	"                                                                                "  // 24
};

// Game over screen display content.
const char MenusAndPrompts::GameOverPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                                                                                ", // 3
	"                  GGGGGGGG     AAA     MM      MM   EEEEEEEE                    ", // 4
	"                 GGG          AAAAA    MMM    MMM   EEEE                        ", // 5
	"                 GGG   GGG   AA   AA   MMMM  MMMM   EEEEEE                      ", // 6
	"                 GGG    GG   AAAAAAA   MM  MM  MM   EEEE                        ", // 7
	"                  GGGGGGGG   AA   AA   MM      MM   EEEEEEEE                    ", // 8
	"                                                                                ", // 9
	"                   OOOOO   VVV      VVV   EEEEEEEE   RRRRR                      ", // 10
	"                  OOO OOO   VVV    VVV    EEEE      RRR  RR                     ", // 11
	"                 OOO   OOO   VVV  VVV     EEEEEE    RRRRRR                      ", // 12
	"                  OOO OOO     VVVVVV      EEEE      RRR  RR                     ", // 13
	"                   OOOOO        VVV       EEEEEEEE  RRR   RR                    ", // 14
	"                                                                                ", // 15
	"                                                                                ", // 16
	"                                                                                ", // 17
	"                       ###########################                              ", // 18
	"                      #     YOU FAILED MISERABLY     #                          ", // 19
	"                       ###########################                              ", // 20
	"                                                                                ", // 21
	"                  Maybe try again? Or was that your best?                       ", // 22
	"                                                                                ", // 23
	"                                                                                "  // 24
};

// Instructions and keys display content.
const char MenusAndPrompts::Instructions_And_KeysPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//	          10         20        30       40        50        60        70        80
	  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ",//0
		"How to Play:                                                                   ",//1
		"* Rescue Pauline ($) by reaching her position without losing all lives.        ",//2
		"* Falling >5 floors, being hit by a barrel, or near an exploding barrel costs  ",//3
		"  a life. Lose all lives, and the game is over.                                ",//4
		"* Collect the hammer (P) to kill enemies within 2 characters.                  ",//5
		"* Collect '+' to gain 50 loops of immunity from enemies, not falls/explosions. ",//6
		"                                                                               ",//7
		"Keys to Control Mario:                                                         ",//8
		"- Move Left:   A or a  | Move Right:   D or d   | Climb Up:    W or w          ",//9
		"- Climb Down:  X or x  | Stay in Place: S or s  | Use Hammer:  P or p          ",//10
		"                                                                               ",//11
		"HUD Information:                                                               ",//12
		"* Lives: Displays Mario's remaining lives.                                     ",//13
		"* Score: Tracks points for avoiding barrels, killing enemies, and fast finish. ",//14
		"* Hammer: Displays 'P' when Mario holds the hammer.                            ",//15
		"* Immortal: Displays '+' during immunity and warns in last 10 loops.           ",//16
		"* Loops: Shows the number of game loops elapsed in the level.                  ",//17
		"                                                                               ",//18
		"Scoring System:                                                                ",//19
		"- Kill enemies: +100 pts  | Avoid barrels: +100 pts  | No damage: +300 pts     ",//20
		"- Fast completion: Bonus decreases with time  | Collect '+': +200 pts          ",//21
		"- Strike penalty: -250 pts                                                     ",//22
		"                                                                               ",//23
		"Press ESC to return to main menu                                               ",//24
};




// Pause screen display content.
const char MenusAndPrompts::PausedGamePrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "                                                                                ", // 0
	 "                                                                                ", // 1
	 "                                                                                ", // 2
	 "                                                                                ", // 3
	 "                      PPPPP    AAA    U   U   SSSSS   EEEE                      ", // 4
	 "                      P   PP  A   A   U   U   S       E                         ", // 5
	 "                      PPPPP   AAAAA   U   U   SSSSS   EEEE                      ", // 6
	 "                      P       A   A   U   U       S   E                         ", // 7
	 "                      P       A   A    UUU    SSSSS   EEEE                      ", // 8
	 "                                                                                ", // 9
	 "                      Are you sure you want to return                           ", // 10
	 "                            to the main menu?                                   ", // 11
	 "                                                                                ", // 12
	 "                                                                                ", // 13
	 "                      Press [ESC] to continue the game                          ", // 14
	 "                      Press [r] to return to the main menu                      ", // 15
	 "                                                                                ", // 16
	 "                                                                                ", // 17
	 "                                                                                ", // 18
	 "                                                                                ", // 19
	 "                                                                                ", // 20
	 "                                                                                ", // 21
	 "                                                                                ", // 22
	 "                                                                                ", // 23
	 "                                                                                "  // 24
};


const char MenusAndPrompts::InvalidFilePrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                                                                                ", // 3
	"                                                                                ", // 4
	"                                                                                ", // 5
	"           IIIIII  NNN   NNN  VVV   VVV  AAA   LL    IIIIII  DDDDD              ", // 6
	"             II    NNNN  NNN   VV   VV  AAAAA  LL      II    DD  DD             ", // 7
	"             II    NNNNN NNN    VV VV  AA   AA LL      II    DD   DD            ", // 8
	"             II    NNNNNNNNN     VVV   AAAAAAA LL      II    DD   DD            ", // 9
	"           IIIIII  NNN   NNN      V    AA   AA LLLLL IIIIII  DDDDDD             ", // 10
	"                                                                                ", // 11
	"                         FFFFF  IIIIII  LL     EEEEEE                           ", // 12
	"                         FF       II    LL     EE                               ", // 13
	"                         FFFF     II    LL     EEEE                             ", // 14
	"                         FF       II    LL     EE                               ", // 15
	"                         FF     IIIIII  LLLLL  EEEEEE                           ", // 16
	"                                                                                ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                ", // 23
	"                                                                                "  // 24
};

const char MenusAndPrompts::NoFilesPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                                                                                ", // 3
	"                                                                                ", // 4
	"                                                                                ", // 5
	"                           NNN   NNN    OOOOO                                   ", // 6
	"                           NNNN  NNN   OOO OOO                                  ", // 7
	"                           NNNNN NNN  OOO   OOO                                 ", // 8
	"                           NNNNNNNNN  OOO   OOO                                 ", // 9
	"                           NNN   NNN   OOO OOO                                  ", // 10
	"                           NNN   NNN    OOOOO                                   ", // 11
	"                                                                                ", // 12
	"                    FFFFF  IIIIII  LL     EEEEEE  SSSSS                         ", // 13
	"                    FF       II    LL     EE     SS                             ", // 14
	"                    FFFF     II    LL     EEEE     SSSSS                        ", // 15
	"                    FF       II    LL     EE           SS                       ", // 16
	"                    FF     IIIIII  LLLLL  EEEEEE  SSSSS                         ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                ", // 23
	"                                                                                "  // 24
};

const char MenusAndPrompts::LevelCompletedPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"                                                                                ", // 0
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                    L      EEEEEE  V     V  EEEEEE  L                           ", // 3
	"                    L      E       V     V  E       L                           ", // 4
	"                    L      EEEE     V   V   EEEE    L                           ", // 5
	"                    L      E         V V    E       L                           ", // 6
	"                    LLLLL  EEEEEE     V     EEEEEE  LLLLL                       ", // 7
	"                                                                                ", // 8
	"        CCCCC   OOOOO  M   M  PPPPP   L      EEEEEE  TTTTT  EEEEEE  DDDDD       ", // 9
	"       C       OOO OOO MM MM  P   PP  L      E         T    E       D    D      ", // 10
	"       C       OOO  OO M M M  PPPPP   L      EEEE      T    EEEE    D     D     ", // 11
	"       C       OOO OOO M   M  P       L      E         T    E       D    D      ", // 12
	"        CCCCC   OOOOO  M   M  P       LLLLL  EEEEEE    T    EEEEEE  DDDDD       ", // 13
	"                                                                                ", // 14
	"                                                                                ", // 15
	"                                                                                ", // 16
	"                                                                                ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                ", // 23
	"                                                                                ", // 24
};

const char MenusAndPrompts::startBySelectFile[Constans::MAX_Y][Constans::MAX_X + 1] =
	{
		//	          10         20        30       40        50        60        70        80
		  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"                                                                               ",//0
			"                                                                               ",//1
			"                                                                               ",//2
			"                                                                               ",//3
			"                                                                               ",//4
			"                select level to start:                                         ",//5
			"                                                                               ",//6
			"                                                                               ",//7
			"                                                                               ",//8
			"                                                                               ",//9
			"                                                                               ",//10
			"                                                                               ",//11
			"                                                                               ",//12
			"                                                                               ",//13
			"                                                                               ",//14
			"                                                                               ",//15
			"                                                                               ",//16
			"                                                                               ",//17
			"                                                                               ",//18
			"                                                                               ",//19
			"                                                                               ",//20
			"                                                                               ",//21
			"                                                                               ",//22
			"                                                                               ",//23
			"                                                                               ",//24
	};

const char MenusAndPrompts::ResultErrorPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//            10         20        30       40        50        60        70        80
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ", //0
		"                                                                               ", //1
		"                                                                               ", //2
		"                                                                               ", //3
		"                                                                               ", //4
		"                                XXX     XXX                                    ", //5
		"                                 XXX   XXX                                     ", //6
		"                                  XXX XXX                                      ", //7
		"                                   XXXXX                                       ", //8
		"                                  XXX XXX                                      ", //9
		"                                 XXX   XXX                                     ", //10
		"                                XXX     XXX                                    ", //11
		"                                                                               ", //12
		"                                                                               ", //13
		"                                                                               ", //14
		"                                                                               ", //15
		"                                                                               ", //16
		"                                                                               ", //17
		"                                                                               ", //18
		"                                                                               ", //19
		"                                                                               ", //20
		"                                                                               ", //21
		"                                                                               ", //22
		"                                                                               ", //23
		"                                                                               ", //24
};



const char MenusAndPrompts::ResultSuccessPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//	          10         20        30       40        50        60        70        80
	  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ",//0
		"                                                                               ",//1
		"                                                                               ",//2
		"                                                                               ",//3
		"                                                                               ",//4
		"               The comparison to the RESULT file was successful!               ",//5
		"                    press any key to move to the next screen                   ",//6
		"                                                                               ",//7
		"                                                                               ",//8
		"                                                                               ",//9
		"                                                                               ",//10
		"                                                                               ",//11
		"                                                                               ",//12
		"                                                                               ",//13
		"                                                                               ",//14
		"                                                                               ",//15
		"                                                                               ",//16
		"                                                                               ",//17
		"                                                                               ",//18
		"                                                                               ",//19
		"                                                                               ",//20
		"                                                                               ",//21
		"                                                                               ",//22
		"                                                                               ",//23
		"                                                                               ",//24
};

const char MenusAndPrompts::AllLevelsComparationSuccessPrompt[Constans::MAX_Y][Constans::MAX_X + 1] =
{
	//            10         20        30       40        50        60        70        80
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ", //0
		"                                                                               ", //1
		"                                                                               ", //2
		"                                                                               ", //3
		"                            VVV             VVV                                ", //4
		"                             VVV           VVV                                 ", //5
		"                              VVV         VVV                                  ", //6
		"                               VVV       VVV                                   ", //7
		"                                VVV     VVV                                    ", //8
		"                                 VVV   VVV                                     ", //9
		"                                  VVV VVV                                      ", //10
		"                                   VVVVV                                       ", //11
		"                                                                               ", //12
		"                                                                               ", //13
		"                                                                               ", //14
		"        Every level run matches exactly the corresponding result file!         ", //15
		"                        press any key to finish session!                       ", //16
		"                                                                               ", //17
		"                                                                               ", //18
		"                                                                               ", //19
		"                                                                               ", //20
		"                                                                               ", //21
		"                                                                               ", //22
		"                                                                               ", //23
		"                                                                               ", //24
};


void MenusAndPrompts::printPrompts(Prompts srn)
{
	gotoxy(0, 0);
	const char(*selectedArray)[Constans::MAX_X + 1] = nullptr;
	// Map the enum to the corresponding array.
	switch (srn) {
	case Prompts::MainMenuScreen:
		selectedArray = MainMenu;
		break;
	case Prompts::WinningPromptScreen:
		selectedArray = WinningPrompt;
		break;
	case Prompts::GameOverPromptScreen:
		selectedArray = GameOverPrompt;
		break;
	case Prompts::Instructions_And_KeysPromptScreen:
		selectedArray = Instructions_And_KeysPrompt;
		break;
	case Prompts::PausedGamePromptScreen:
		selectedArray = PausedGamePrompt;
		break;
	case Prompts::InvalidFilePromptScreen:
		selectedArray = InvalidFilePrompt;
		break;
	case Prompts::NoFilesPromptScreen:
		selectedArray = NoFilesPrompt;
		break;
	case Prompts::LevelCompletedPromptScreen:
		selectedArray = LevelCompletedPrompt;
		break;
	case Prompts::startBySelectFileScreen:
		selectedArray = startBySelectFile;
		break;

	case Prompts::ResultErrorPromptScreen:
		selectedArray = ResultErrorPrompt;
		break;

	case Prompts::ResultSuccessPromptScreen:
		selectedArray = ResultSuccessPrompt;
		break;

	case Prompts::AllLevelsComparationSuccessPromptScreen:
		selectedArray = AllLevelsComparationSuccessPrompt;
		break;
	}

	if (selectedArray != NULL)
	{
		for (int i = 0; i < Constans::MAX_Y - 1; i++)
		{
			std::cout << selectedArray[i] << '\n';
		}
		std::cout << selectedArray[Constans::MAX_Y - 1];
		if (srn == Prompts::GameOverPromptScreen || srn == Prompts::InvalidFilePromptScreen)
		{
			Sleep(SLEEP_IN_PROMPTS);
		}
		clearInputBuffer();

	}

}

// Score arr represents in each cell how many points player achieved in each score catagory:
// ScoreArr[0]: speed bonus, ScoreArr[1]: enemy kill bonus, ScoreArr[2]: strikes Penalty, ScoreArr[3]: no damage bonus,  ScoreArr[4]: total score for this level
// We will display each catagory of score only if it relevant for this stage
void MenusAndPrompts::printLevelCompletedPrompt(int _numStrikes, int _numEnemyKilled, int _levelLoopsCounter, bool isPlusPicked, int* scoreArr)
{
	printPrompts(Prompts::LevelCompletedPromptScreen);
	int counterLines = 0;
	// Display explenations on the score achieved in the level. 
	gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
	std::cout << "Speed Completion Bonus:   +" << scoreArr[0] << " points (loops: " << _levelLoopsCounter << ")";
	counterLines++;

	if (_numEnemyKilled > 0)
	{
		gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
		std::cout << "Enemy Killing Bonus:      +" << scoreArr[1] << " points (" << _numEnemyKilled << " enemies killed)";
		counterLines++;
	}
	if (_numStrikes > 0)
	{
		gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
		std::cout << "Life Penalty:             " << scoreArr[2] << " points (" << _numStrikes << " lives lost)";
		counterLines++;
	}
	else
	{
		gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
		std::cout << "No Damage Bonus:          +" << scoreArr[3] << " points";
		counterLines++;
	}

	if (isPlusPicked)
	{
		gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
		std::cout << "Collecting plus bonus:      +" << scoreArr[4] << " points";
		counterLines++;
	}
	gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
	std::cout << "---------------------------------\n";
	counterLines++;
	gotoxy(START_DISPLAY_SCORE_DATA_X, START_DISPLAY_SCORE_DATA_Y + counterLines);
	std::cout << "Total Score for Level:    " << scoreArr[5] << " points\n";
	counterLines++;
	Sleep(SLEEP_IN_PROMPTS);
}

void MenusAndPrompts::printWinningPrompt(int finalScore)
{
	printPrompts(Prompts::WinningPromptScreen);
	gotoxy(START_FINAL_DISPLAY_SCORE_DATA_X, START_FINAL_DISPLAY_SCORE_DATA_Y);
	// Displaying the final score of this session
	std::cout << "Total Score for the Game: " << finalScore << " points" << std::endl;
	gotoxy(START_FINAL_DISPLAY_SCORE_DATA_X, START_FINAL_DISPLAY_SCORE_DATA_Y + 2);
	std::cout << "Thank you for playing Donkey Kong!" << std::endl;
	Sleep(SLEEP_IN_PROMPTS);
}



#pragma once
#include "Mario.h"
#include "EnemyVEC.h"
#include "Steps.h"
#include "Results.h"
class Game
{

	static constexpr int ACTIVATE_BARREL_DELAY = 15; // Decent time to activate new barrel. 
	static constexpr int LOOPS_OF_PLUS_IMMORTALITY = 50; //The amount of loops mario is immortal when picking plus.

	// Constants for score calculations
    const int COLLECTIBLE_BONUS = 200;
	static constexpr int NO_DAMAGE_BONUS = 300;
	static constexpr int TIME_BONUS_DIVISOR = 240000;
	static constexpr int LIFE_PENALTY = -250;
	static constexpr int ENEMY_DEFEAT_BONUS = 100;

	Point KongPos;
	Point hammerPos;
	Point plusPos;
	bool isPlusAppeared = false; //Flag to indticate if screen contain plus.


protected:
	static constexpr int START_LIFE = 3; // Initial number of lives.
	std::vector<std::string> LevelNamesVEC;
	size_t counterGameLoops = 0; // Tracks the number of game loop iterations.
	Mario player;
	bool is_P_Pressed = false;  // Indicates player pressed p
	Point PaulinePos;
	Board myBoard; // The game board.
	MenusAndPrompts presentPrompts;
	HUD hud;
	int totalScore = 0; //Initial score.

	bool isPlusActivated = false;  //Flag to indticate if plus is picked up and activated.
	int immortalCounter = LOOPS_OF_PLUS_IMMORTALITY;//counts the amount of loops mario will be immortal.
	bool isPlusAlreadyActivated = false; //Flag to indicate that + is already picked.

public:
	//Game ctor
	Game(): player(&myBoard) {}

	virtual ~Game() {}; // Virtual dtor for game.

	//Prototypes
	bool RunLevel(std::string fileName, bool* isValidFile, int* enemyKillCounter, int* numStrikes);
	virtual void RunGame() = 0; // Runs the entire game.
	bool isWonLevel(const Mario& player) const; // Checks and returns if the player has won the game.
	bool isGameOver(const Mario& player) const; // Checks and returns if the game is over.

	void calcScore(int numStrikes, int numEnemyKilled, int* scoreArr); // Function to calculate the score.

	int calcTotalScore(int numStrikes, int numEnemyKilled); //Function that calculates only the total score for spesific level.

	//Abstract virtual functions
	virtual void handleStartOfLevel(Steps& currSteps, Results& currRes, std::string fileName) = 0;

	virtual bool handleInput(size_t iteration, Results& currRes, Steps& currStep, std::string fileName) = 0;

	virtual bool handleFilesAfterStrike(size_t iteration, Results& currRes, std::string fileName) = 0;

	virtual bool handleEndOfLevel(Steps& currSteps, Results& currRes, int levelScore, std::string fileName, size_t iteration) = 0;

	virtual bool handleInvalidFile(std::string fileName) = 0;

	virtual void handleSleep() = 0;

	// Function that takes all available files, and sorting their names in vector lexicographically.
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);

	void represent_P_AfterStrike();

};


#include "Game.h"



// Runs a single level of the game.
// The function gets level file name, and an output variable if the file is invalid.
// Also, the function gets output variable to count enemy killed and return if user wants to return to main menu.
// All displays and prints are activated just if the game is not in silent mode.
bool Game::RunLevel(std::string fileName, bool* isValidFile, int* enemyKillCounter, int* numStrikes)
{
	isPlusAlreadyActivated = false;
	//Resets counter for picking plus.
	immortalCounter = LOOPS_OF_PLUS_IMMORTALITY;
	//Resets counterGameLoops
	counterGameLoops = 0;
	// If the file is invaild present invalid file screen, and return to RunGame with true flag - meaning you can continue the session.
	if (!myBoard.load(fileName))
	{
		*isValidFile = false;
		return handleInvalidFile(fileName);
	}
	myBoard.present(); // Displays the game board.
	
	// Next to rows set mario to his initial state with his updated startPos.
	player.setMarioStartPos(myBoard.GetStartMarioPos());
	player.resetMarioMembers();

	// Sets all game obgets to their start positions.
	PaulinePos = myBoard.GetStartPaulinePos();
	KongPos = myBoard.GetStartDonkeyKongPos();
	hud = HUD(myBoard.GetStart_L_Pos());
	hammerPos = myBoard.GetStartHammerPos();
	EnemyVEC eVEC(&myBoard, KongPos, myBoard.Get_StartGhostsVEC_Pos());

	//If Plus startPos is nor (-1,-1), that means that plus appear in screen.
	if (myBoard.GetStartPlusPos() != Point(-1,-1))
	{
		plusPos = myBoard.GetStartPlusPos();
		isPlusAppeared = true;
	}

	Steps currStep;
	Results currRes;
	bool isMarioDiedByFall = false;
	handleStartOfLevel(currStep, currRes, fileName);
	eVEC.resetEnemies();

	hud.displayHUD(player.getCurLife(), totalScore, player.getIsHoldingHammer(), counterGameLoops, is_P_Pressed, isPlusActivated, immortalCounter);

	// Main game loop for the level, continues while game is not over or the player hasn't won yet.
	while (!isWonLevel(player) && !isGameOver(player))
	{
		if (handleInput(counterGameLoops, currRes, currStep, fileName))
		{
			return false;
			immortalCounter = 0;
		}

		// Every game iteretion update the loops counter and p pressed in the HUD.
		hud.displayLoops(counterGameLoops);
		hud.display_P_Pressed(is_P_Pressed);
		
		// if Plus Activated, handle HUD and counter.
		if (isPlusActivated)
		{
			immortalCounter--;
			//If there is less then 11 loops to immortality, display unique hud display.
			if (immortalCounter <= 10)
			{
				//Immortal ability has ended.
				if (immortalCounter == 0)
				{
					isPlusActivated = false;
					isPlusAppeared = false; // In order to pick plus once every level, we will change thi flag to false.
				}
				hud.displayPlusState(isPlusActivated, immortalCounter);
			}
		}

		if (counterGameLoops % ACTIVATE_BARREL_DELAY == 0)
		{
			eVEC.AddBarrel(); // Activate a new barrel periodically.
		}		

		if (!SilentState::getSilentMode())
		{
			player.drawM(); // Draw Mario.
			eVEC.drawEnemies(); // Draw enemies.
			handleSleep();
		}
		// Checks if mario have Hammer and pressed p to kill
		if (player.getIsHoldingHammer() && is_P_Pressed)
		{
			// Checks if mario killed enemys, handle thier death, sum how many died, and send them to score calc.
			// Also, update the enemy kill counter.
			*enemyKillCounter += eVEC.handleEnemyStrikedByHammer(player.getMarioPos());
		}

		// FIrst mario death check: checking if mario died by falling, by going near a barrel explosion, or by colliding with barrels.
		// the checks need to be here because isMarioInExplosionRadius is also handle barrel explosion and we want all the other objects
		// to be visible in that stage, and also in order to prevent mario move another step after death by fall.
		//Note: if plus is activated, mario is immortal for collisions, not for explosion and fall.
		if (isMarioDiedByFall || (!isPlusActivated && eVEC.checkCollision(player.getMarioPos())) || eVEC.isMarioInExplosionRadius(player.getMarioPos()))
		{
			player.handleStrike(); // Handle Mario's life loss.
			player.setMarioStartPos(myBoard.GetStartMarioPos()); // Reset Mario's position to the starting point.
			(*numStrikes)++;
			if (!isGameOver(player))
			{
				eVEC.resetEnemies(); // Reset enemies after collision.
				isMarioDiedByFall = false; 
				// Update the HUD.
				hud.displayHUD_AfterStrike(player.getCurLife());
				is_P_Pressed = false;
				// Return P symbol to the screen.
				represent_P_AfterStrike();
				clearInputBuffer();
				if (isPlusActivated)
				{
					isPlusAppeared = false;
					isPlusActivated = false;
					hud.displayPlusState(false);
				}
			}
			if (!handleFilesAfterStrike(counterGameLoops, currRes, fileName))
			{
				return false;
			}
			
			continue;
		}

		if (!SilentState::getSilentMode())
		{
			player.drawM_Back(); // Erase Mario's previous position.
			eVEC.drawBackEnemies(); // Erase enemie's previous positions.
		}

		isMarioDiedByFall = player.marioMovement();// Update Mario's position. Returns true if Mario died by falling.
		eVEC.moveEnemies();  // Move all enemies.

		// Second mario death check (after movement of barrels and mario):
		// Checks the edge case where mario and barrel moved in opposite direction and switched places because we moved both of them
		//what should be collision. we check that here because we need to do that after movement.
		//Note: if plus is activated, mario is immortal for collisions, not for explosion and fall.
		if (!isPlusActivated && eVEC.isMarioAndEnemySwitchAndHit(player.getMarioPos(), player.getMarioPrevPos()))
		{
			player.handleStrike(); // Handle Mario's life loss.
			player.setMarioStartPos(myBoard.GetStartMarioPos()); // Reset Mario's position to the starting point.
			(*numStrikes)++;
			if (!isGameOver(player))
			{
				eVEC.resetEnemies(); // Reset enemies after collision.
				isMarioDiedByFall = false;
				//Update the HUD.
				hud.displayHUD_AfterStrike(player.getCurLife());
				// Return P symbol to the screen.
				represent_P_AfterStrike();
				clearInputBuffer();
				//Checks if mario died from fall or explosion during immortal phase,
				// and if so turn off immortality and do that mario can't get + again.
				if (isPlusActivated)
				{
					isPlusAppeared = false;
					isPlusActivated = false;
					hud.displayPlusState(false);
				}
				continue;
			}
			if (!handleFilesAfterStrike(counterGameLoops, currRes, fileName))
			{
				return false;
			}
		} 
		
		//update that variable so pressing p work only maximum of 1 iteration
		is_P_Pressed = false;

		// Remove inactive enemys fron enemy's vectors.
		eVEC.removeInactive();

		// If mario meets hammer, he is holding him.
		if (player.getMarioPos() == hammerPos)
		{
			player.setToHoldHammer();
			myBoard.setCharInBoard(hammerPos.getCurX(), hammerPos.getCurY(), ' ');
			hud.displayHammer(player.getIsHoldingHammer());
		}

		// If mario meets plus, and he hadn't picked the plus yet, mario will hold him. initilize flags and counter
		if (isPlusAppeared && player.getMarioPos() == plusPos)
		{
			myBoard.setCharInBoard(plusPos.getCurX(), plusPos.getCurY(), ' ');
			immortalCounter = LOOPS_OF_PLUS_IMMORTALITY;
			isPlusActivated = true;
			isPlusAlreadyActivated = true;
			hud.displayPlusState(true, immortalCounter);
		}
		counterGameLoops++; // Increment game loop counter.
	}

	return handleEndOfLevel(currStep, currRes, calcTotalScore(*numStrikes, *enemyKillCounter), fileName, counterGameLoops);
}


// Checks if the player has reached the princess (win condition).
bool Game::isWonLevel(const Mario& player) const
{
	return player.getMarioPos() == PaulinePos;
}

// Checks if the game is over (Mario's lives reach zero).
bool Game::isGameOver(const Mario& player) const
{
	return player.getCurLife() <= 0;
}

// Score arr represents in each cell how many points player achieved in each score catagory:
// ScoreArr[0]: speed bonus, ScoreArr[1]: enemy kill bonus, ScoreArr[2]: strikes Penalty, ScoreArr[3]: no damage bonus, ScoreArr[4]: collecting + bonus  ScoreArr[5]: total score for this level.
void Game::calcScore(int numStrikes, int _numEnemyKilled, int* scoreArr)
{

	scoreArr[0] = TIME_BONUS_DIVISOR / (int)counterGameLoops;
	scoreArr[1] = _numEnemyKilled * ENEMY_DEFEAT_BONUS;
	if (numStrikes != 0)
	{
		scoreArr[2] = numStrikes * LIFE_PENALTY;
		scoreArr[3] = 0;
	}
	else
	{
		scoreArr[2] = 0;
		scoreArr[3] = NO_DAMAGE_BONUS;
	}
	if (isPlusAlreadyActivated)
	{
		scoreArr[4] = COLLECTIBLE_BONUS;
	}
	else
	{
		scoreArr[4] = 0;
	}
	scoreArr[5] = 0;
	for (int i = 0; i < 4; i++)
	{
		(scoreArr)[5] += (scoreArr)[i];
	}
}

//Function that calculates only the total score for spesific level.
int Game::calcTotalScore(int numStrikes, int numEnemyKilled)
{
	int res = (TIME_BONUS_DIVISOR / (int)counterGameLoops) + numEnemyKilled * ENEMY_DEFEAT_BONUS;
	if (isPlusAlreadyActivated)
	{
		res += COLLECTIBLE_BONUS;
	}
	if (numStrikes != 0)
	{
		res+= numStrikes * LIFE_PENALTY;
	}
	else
	{
		res += NO_DAMAGE_BONUS;
	}
	return res;
}

void Game::represent_P_AfterStrike()
{
	myBoard.setCharInBoard(hammerPos.getCurX(), hammerPos.getCurY(), Constans::HAMMER_SYMBOL);
	if (!SilentState::getSilentMode())
	{
		hammerPos.draw();
	}
}


// Function that takes all available files, and sorting their names in vector lexicographically.
void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill)
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		// Checks if the file is one of the screen files.
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen" && fs::is_regular_file(entry.path()))
		{
			vec_to_fill.push_back(filenameStr);
		}
	}

	//Sorts the file names in vector lexicographically.
	std::sort(vec_to_fill.begin(), vec_to_fill.end(), [](const std::string& a, const std::string& b) {
		int numA = std::stoi(a.substr(6, 2));
		int numB = std::stoi(b.substr(6, 2));
		return numA < numB;
		});
}


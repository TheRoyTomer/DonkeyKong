#include "Mario.h"

// Checks if key pressed is 'a' or 's' or 'd' or 'w' or 'x' or 'p'
bool Mario::validKey(const char key) const
{

	for (int i = 0; i < numKeys; i++)
	{
		if (std::tolower(key) == movementKeys[i] || std::tolower(key) == Constans::HAMMER_SYMBOL)
		{
			return true;
		}
	}
	return false;
}

// Checks if the given key press is a valid move for Mario.
bool Mario::validMovementKey(const char key) const
{
	// Prevent downward movement if Mario is on the floor and you are not climbing down.
	if (curBoard->isFloorBelow(p) && (p.getCurY() < 23 && !curBoard->isLadderTwoCharsBelow(p)))
	{
		if (key == movementKeys[(int)(Constans::DirNames::DOWN)])
		{
			return false;
		}
	}

	// Restrict upward and downward movement if out of vertical bounds.
	if (key == movementKeys[(int)(Constans::DirNames::UP)] && p.getNextMoveY() <= 0)
	{
		return false;
	}
	if (key == movementKeys[(int)(Constans::DirNames::DOWN)] && p.getNextMoveY() >= Constans::MAX_Y - 1)
	{
		return false;
	}

	// Restrict left or right movement if climbing.
	// Moreover, in the single step in climbing when we are on a floor, we also can't Stay.
	if (climbFlag)
	{
		if ((key == movementKeys[(int)(Constans::DirNames::RIGHT)] || key == movementKeys[(int)(Constans::DirNames::LEFT)]))
		{
			return false;
		}
		if (curBoard->isOnFloor(p) && key == movementKeys[(int)(Constans::DirNames::STAY)])
		{
			return false;
		}

	}

	//Restrict movement to horizontal directions if jumping or falling.
	if (jumpFlag || fallFlag)
	{
		if ((key != movementKeys[(int)(Constans::DirNames::RIGHT)] && key != movementKeys[(int)(Constans::DirNames::LEFT)]))
		{
			return false;
		}
	}

	// Prevent downward movement if near the bottom edge or floor.
	if (p.getCurY() >= Constans::MAX_Y - 2 || (curBoard->isFloorBelow(p) && !curBoard->isLadderTwoCharsBelow(p)))
	{
		if (key == movementKeys[(int)(Constans::DirNames::DOWN)])
		{
			return false;
		}
	}
	return true; // Key is valid for movement.
}

// Processes a valid key press and adjusts Mario's direction accordingly.
void Mario::keyPressed(char key)
{
	for (int i = 0; i < numKeys; i++)
	{
		if (std::tolower(key) == movementKeys[i])
		{
			if (validMovementKey(key))
			{
				prevDirX = p.getDirX(); // Store the previous X direction.
				p.setDirByDirName(Constans::DirNames(i));  // Update Mario's direction with enum dirNames in Constans class.
				return;
			}
		}
	}
}

// Validates if the next move is within the board's boundaries.
bool Mario::checkNextStepValid()
{
	Point nextStep(p.getNextMoveX(), p.getNextMoveY());
	bool inBounderies_X_Flag = curBoard->checkIfIn_X_Boundaries(nextStep);
	bool inBounderies_Y_Flag = curBoard->checkIfIn_Y_Boundaries(nextStep);
	//If Mario's next step is in baunderies, the next step is valid.
	if (inBounderies_X_Flag && inBounderies_Y_Flag)
	{
		return true;
	}
	//If Mario's next step is not in X baunderies, reset X direction to 0.
	else if (inBounderies_X_Flag)
	{
		p.resetDirY();
	}
	//If Mario's next step is not in Y baunderies, reset Y direction to 0.
	else if (inBounderies_Y_Flag)
	{
		p.resetDirX();
	}
	//If Mario's next step is not in X and Y baunderies, reset direction to {0,0}.
	else
	{
		p.resetDirX();
		p.resetDirY();
	}

	climbFlag = false;
	return false;
}

// Handles Mario's movement logic, including jumping, climbing, and falling.
bool Mario::marioMovement()
{
	bool isDiedByFall = false;
	if (checkNextStepValid())
	{
		// Handle movement while going up.
		if (p.getDirY() == -1)
		{
			// Conditions for Mario to climb up.
			if ((climbFlag || curBoard->isOnLadder(p)) && !jumpFlag)
			{	
				climbUp();
			}
			// If Mario is going upwords and is not climbing up, it means he is jumping.
			else
			{
				jump();
			}
		}
		else
		{
			// Conditions for Mario to climb down.
			if (p.getDirY() == 1 && !fallFlag)
			{
				climbDown();
			}
			// Conditions for Mario to fall.
			if ((!curBoard->isFloorBelow(p) && !climbFlag) || fallFlag)
			{
				
				isDiedByFall = marioFall();
			}
		}
	}
	// If Mario's next step is invalid but he is still on the air, make him fall.
	else if(fallFlag)
	{
		isDiedByFall = marioFall();
	}
	// If Mario's next step is invalid but he is still in jumping prosses, stop jumping prosses and make him fall.
	else if (jumpFlag)
	{
		fallFlag = true;
		jumpFlag = false;
		jumpStep = 0;
		isDiedByFall = marioFall();
	}
	if (!isDiedByFall)
	{
		p.move(); // Update Mario's position.
	}
	return isDiedByFall;
}

// Handles Mario climbing upward on ladders.
void Mario::climbUp()
{
	// Handles first step of climb.
	if (curBoard->isFloorBelow(p) && curBoard->isOnLadder(p))
	{
		climbFlag = true;
	}
	// Handles last step of climb.
	if (curBoard->isOnFloor(p) && curBoard->isLadderBelow(p))
	{
		p.decreaseCur_Y_ByOne(); // Take Mario one charecter up, in order to do not be on a floor.
		p.setDirByDirName(Constans::DirNames::STAY); //Change his direction to STAY.
		climbFlag = false; 
	}
}

// Handles Mario climbing downward on ladders.
void Mario::climbDown()
{
	// Handles first step of climb.
	if (curBoard->isFloorBelow(p) && curBoard->isLadderTwoCharsBelow(p))
	{
		climbFlag = true;
	}
	// Handles last step of climb.
	if (curBoard->isOnLadder(p) && curBoard->isFloorBelow(p))
	{
		p.setDirByDirName(Constans::DirNames::STAY);//Change his direction to STAY.
		climbFlag = false;
	}
}

// Handles Mario's jumping logic.
void Mario::jump()
{
	switch (jumpStep)
	{
	case 0: //First step of a jump.
		p.setDirByValues(prevDirX, -1); // X direction changes to his previous direction- in order to continue the movment.
		//if the next move is a floor, you can't jump. your dirY will reset to 0 and you will continue in your previous X movement direction
		if (curBoard->isNextMoveFloor(p))
		{
			p.resetDirY();
		}
		else
		{
			jumpFlag = true;
			jumpStep++;
		}
		break;

	case 1: // Second step of a jump. 
		// If the next step is floor, start fall process.
		if (curBoard->isNextMoveFloor(p))
		{
			marioFall();
		}
		else
		{
			jumpStep++;
		}
		break;

	case 2: // Third step of a jump, start fall process.
		marioFall();
		break;
	}
}

// Handles Mario's falling logic and checks for death due to falling too far.
bool Mario::marioFall()
{
	// Handles first step of fall.
	if (p.getDirY() != 1)
	{
		// Beacuse jump calls to fall function when finish, we stop the jump process here, in order to avoid edge cases where for example, the user press another key at the peak of the jump,
		// which cause problems in ending the jump process. so here, we ensure the jump process has ended.
		if (jumpFlag)
		{
			jumpFlag = false;
			jumpStep = 0;
		}
		fallFlag = true;
		p.setDirByValues(p.getDirX(), 1);
	}

	// Handles last step of fall.
	if (curBoard->isNextMoveFloor(p))
	{
		fallFlag = false;
		p.resetDirY();
		// If Mario falls more floors than allowed, return true for die by fall.
		if (countFallFloors >= MARIO_MAX_FLOORS_TO_FALL)
		{
			return true;
		}
		else
		{
			countFallFloors = 0;//Resets the counter.
		}
	}
	// Mario mid fall process, increase caunter by 1.
	else
	{
		countFallFloors++;
	}
	return false;
}

// Change all mario's data members to thier initial state.
void Mario::resetMarioMembers()
{
	climbFlag = false;
	fallFlag = false;
	jumpFlag = false;
	isHoldingHammer = false;
	countFallFloors = 0;
	prevDirX = 0;
	jumpStep = 0;
	p.setDirByDirName(Constans::DirNames::STAY);
}

// Handles events when Mario is struck, such as losing a life and resetting position.
void Mario::handleStrike()
{
	p.setDirByDirName(Constans::DirNames::STAY);
	curLife--;
	resetMarioMembers(); // Resets all mario data members to thier initial state.
	if (!SilentState::getSilentMode())
	{
		strikeAnimation(); // Play strike animation.
	}
}


// Plays an animation when Mario is struck.
void Mario::strikeAnimation()
{
	for (int i = 0; i < EXPLODE_ITERATIONS; i++)
	{
		p.erase();
		Sleep(SLEEP_EXPLODE_ANIMATION);
		p.draw();
		Sleep(SLEEP_EXPLODE_ANIMATION);
	}
	drawM_Back();
	
}
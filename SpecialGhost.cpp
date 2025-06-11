#include "SpecialGhost.h"

// The function will determine if special ghost should climb, with possibility of 15% to do so.
bool SpecialGhost::isStartClimb()
{
	if (PROBABILITY_TO_CLIMB < getRandomNumber(RANGE_START_IF_CLIMBING, RANGE_END_IF_CLIMBING))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Checks if we are in a valid position to climb upwards.
bool SpecialGhost::ifCanStartClimbUp()
{
	return enemyCurBoard->isFloorBelow(p) && enemyCurBoard->isOnLadder(p) && p.getCurY() != 0;
}

//Checks if we are in a valid position to climb downwards.
bool SpecialGhost::ifCanStartClimbDown()
{
	return enemyCurBoard->isFloorBelow(p) && enemyCurBoard->isLadderTwoCharsBelow(p);
}

// Handles Special Ghost's climbing upward on ladders.
void SpecialGhost::climbUp()
{
	// Handles last step of climb - stopping it.
	if (enemyCurBoard->isOnFloor(p) && enemyCurBoard->isLadderBelow(p))
	{
		p.decreaseCur_Y_ByOne(); // Take Special ghost one charecter up, in order to do not be on a floor.
		p.setDirByDirName(Constans::DirNames::STAY); //Change his direction to STAY.
		climbFlag = false;
	}
}

// Handles Special Ghost's climbing downward on ladders.
void SpecialGhost::climbDown()
{
	// Handles last step of climb - stopping it.
	if (enemyCurBoard->isOnLadder(p) && enemyCurBoard->isFloorBelow(p))
	{
		p.setDirByDirName(Constans::DirNames::STAY); //Change his direction to STAY.
		climbFlag = false;
	}
}

// Handles the special ghost's movement and state changes.
void SpecialGhost::enemyMovement()
{
	if (ifCanStartClimbUp() && !climbFlag && isStartClimb())
	{
		climbFlag = true;
		p.setDirByDirName(Constans::DirNames::UP);
		isOnOneFloorFlag = false;
	}
	else if (ifCanStartClimbDown() && !climbFlag && isStartClimb())
	{
		climbFlag = true;
		p.setDirByDirName(Constans::DirNames::DOWN);
		p.increaseCur_Y_ByOne();
		isOnOneFloorFlag = false;
	}
	
	if (!isOnOneFloorFlag)
	{
		if (p.getDirX() == 0 && p.getDirY() == 0)
		{
			SetRandHorizontalDir(); //Change his direction to LEFT or RIGHT randomly.
		}
		else if (climbFlag)
		{
			if (p.getDirY() == -1)
			{
				climbUp();
			}
			else
			{
				climbDown();
			}
			if (!isNextMoveInBounderies() /*|| isDirectionNeedChange()*/)
			{
				flipGhostDir();
			}
		}

		if (!isNextEnemyStepValid() && !climbFlag)
		{
			flipGhostDir();
		}
		else if (!enemyCurBoard->isNextMoveFloorBelow(p) && !climbFlag)
		{
			flipGhostDir();
			// If there is no floor in both sides of the ghost, change it's direction to STAY and update flag.
			if (!enemyCurBoard->isNextMoveFloorBelow(p))
			{
				isOnOneFloorFlag = true;
				p.setDirByDirName(Constans::DirNames::STAY);
			}
		}
		else if (isDirectionNeedChange())
		{
			flipGhostDir();
		}

		p.move();
	}
}
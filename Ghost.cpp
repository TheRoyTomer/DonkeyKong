#include "Ghost.h"
//Sets ghost dir to LEFT or RIGHT randomly (for start or in special ghost when finished climbing).
void Ghost::SetRandHorizontalDir()
{
	int startDirX = getRandomNumber(0, 1);
	if (startDirX == 0)
	{
		p.setDirByDirName(Constans::DirNames::LEFT);
	}
	else
	{
		p.setDirByDirName(Constans::DirNames::RIGHT);
	}
}

// Flip the ghost direction
void Ghost::flipGhostDir()
{
	p.setDirByValues(p.getDirX() * -1, p.getDirY() * 1);
}

// According to assignment's demands, the ghost will change direction with the possibility of 5%.
// The function will determine if change of direction is needed.
bool Ghost::isDirectionNeedChange()
{
	if (PROBABILITY_TO_CHANGE_DIR < getRandomNumber(RANGE_START_CHANGE_DIR, RANGE_END_CHANGE_DIR))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Handles the ghost's movement and state changes.
void Ghost::enemyMovement()
{
	// Move unless ghost is standing on a single floor
	if (!isOnOneFloorFlag)
	{
		if (!isNextEnemyStepValid())
		{
			flipGhostDir();
		}
		else if (!enemyCurBoard->isNextMoveFloorBelow(p))
		{
			flipGhostDir();
			// If there is no floor in both sides of the ghost, change it's direction to STAY and update flag.
			if (!enemyCurBoard->isNextMoveFloorBelow(p))
			{
				p.setDirByDirName(Constans::DirNames::STAY);
				isOnOneFloorFlag = true;
			}
		}
		else if (isDirectionNeedChange())
		{
			flipGhostDir();
		}
		p.move();
	}
}


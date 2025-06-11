#include "Barrel.h"

// Assignment operator for barrels.
Barrel& Barrel::operator=(const Barrel& other)
{
	if (this != &other)
	{
		Enemy::operator=(other);
		isFalling = other.isFalling;
		ExplodeFlag = other.ExplodeFlag;
		barrelCountLinesFall = other.barrelCountLinesFall;
		barrelPrevDirX = other.barrelPrevDirX;
	}
	return *this;
}

// Activates the barrel and sets a random path.
bool Barrel::initializeBarrel()
{
	int randNum = getRandomNumber(RANGE_START_BARREL_PATH, RANGE_END_BARREL_PATH);
	switch (randNum)
	{
	case 1:
		setToRightPath();

		break;
	case 2:
		setToLeftPath();

		break;
	case 3:
		setToDownPath();
		if (enemyCurBoard->checkIfIn_Y_Boundaries(p) && enemyCurBoard->isFloorBelow(p))
		{
			p.setDirByDirName(Constans::DirNames::LEFT); // In edge case where barrel goes in down path and immidiatly meats '=' floor
			//If not, it will go through fall algorithm in movement
		}
		break;
	}
	
	// If the barrel we created placed on a floor or out of bounderies, we set to not active
	if (!enemyCurBoard->checkIfIn_X_Boundaries(p) || !enemyCurBoard->checkIfIn_Y_Boundaries(p) || enemyCurBoard->isOnFloor(p))
	{
		return false;
	}
	return true;

}

// Updates the barrel's direction based on the floor type.
void Barrel::changeBarrelDir(int _prevDirX)
{
	if (p.getNextMoveY() == Constans::MAX_Y)
	{
		p.setDirByValues(_prevDirX, 0);
		return;
	}
	switch (enemyCurBoard->getSignFloorBelow(p))
	{
	case Board::FLOOR_RIGHT:
		p.setDirByDirName(Constans::DirNames::RIGHT);
		break;

	case Board::FLOOR_LEFT:
		p.setDirByDirName(Constans::DirNames::LEFT);
		break;

	case Board::FLOOR_NORMAL:
		p.setDirByValues(_prevDirX, 0);
		break;
	}
}

// Handles the barrel's movement and state changes - only if active.
void Barrel::enemyMovement()
{
	// If next step is not valid, change barrel to not active and return.
	if (!isNextEnemyStepValid())
	{
		this->isActive = false;
		return;
	}
	// Checks if barrel's next move is exceeding boundaries, and if so, the barrel dies.
	// Checks if barrel is falling, and if so, activates falling function.
	else if (this->isBarrelFalling() || isFalling)
	{
		this->barrelFall();
	}
	else
	{
		// Checks floor's sign and change barrel's direction accordingly.
		this->changeBarrelDir(p.getDirX());
	}
	if (!ExplodeFlag)
	{
	    p.move(); // Moves the barrel in it's direction
	}
}

// Checks if there isn't a floor under the barrel, and if so, barrel is falling.
bool Barrel::isBarrelFalling() const
{
	if (!(enemyCurBoard->isFloorBelow(p)))
	{
		return true;
	}
	return false;
}

// Manages the barrel's behavior while falling.
void Barrel::barrelFall()
{
	barrelCountLinesFall++; // Increase falling counter by 1.

	// Start falling if not already falling.
	if (p.getDirY() != 1)
	{
		isFalling = true;
		barrelPrevDirX = p.getDirX();
		p.setDirByDirName(Constans::DirNames::DOWN);
	}

	// Stop falling when a floor is reached. 
	if (enemyCurBoard->isFloorBelow(p))
	{
		// Checks if the barrel has fallen more floors then allowed, and if so, trigger an explosion by flag.
		if (barrelCountLinesFall >= B_FALL_FLOORS_TO_DIE)
		{
			ExplodeFlag = true;
		}
		else
		{
			isFalling = false;
			barrelCountLinesFall = 0;
			this->changeBarrelDir(barrelPrevDirX);
		}
	}
}

// Animates the barrel's explosion.
void Barrel::ExplodeAnimation(const Point& marioPos)
{
	int centerX = p.getCurX();
	int centerY = p.getCurY();
	Point temp(centerX, centerY, '*');
	// Stage 1: Center point. Mario cant be where barrel was hit because then barrel hits Mario and not the floor
	{
		if (enemyCurBoard->canDrawExplode(temp))
		{
			temp.draw();
		}
		Sleep(SLEEP_DURING_EXPLODE);
		if (enemyCurBoard->canDrawExplode(temp))
		{
			Point(centerX, centerY, ' ').draw();
		}
	}

	// Stage 2: Points 1 char away (3x3 grid excluding stage 1 center)
		//First, drawing the perimeter.
	{
		for (int disX = -1; disX <= 1; ++disX)
		{
			for (int disY = -1; disY <= 1; ++disY)
			{
				if (disX != 0 || disY != 0) // Skip the center point
				{
					temp.setPointPosition(centerX + disX, centerY + disY);
					if (enemyCurBoard->canDrawExplode(temp) && temp != marioPos)
					{
						temp.draw();
					}
				}
			}
		}
		Sleep(SLEEP_DURING_EXPLODE); // Pause before erasing stage 2

		//Then, restores the background that was in the perimeter.
		for (int disX = -1; disX <= 1; ++disX)
		{
			for (int disY = -1; disY <= 1; ++disY)
			{
				if (disX != 0 || disY != 0) // Skip the center point
				{
					temp.setPointPosition(centerX + disX, centerY + disY);
					temp.setSymbol(enemyCurBoard->getCharFromBoard(centerX + disX, centerY + disY));
					if (enemyCurBoard->canDrawExplode(temp) && temp != marioPos)
					{
						temp.draw();
					}
				}
			}
		}
	}

	// Stage 3: Points 2 chars away (5x5 grid, only the second perimeter of a rectangle)
	//First, drawing the perimeter.
	{
		for (int disX = -2; disX <= 2; ++disX)
		{
			for (int disY = -2; disY <= 2; ++disY)
			{
				if (abs(disX) == 2 || abs(disY) == 2) // Points exactly 2 chars away
				{
					temp.setPointPosition(centerX + disX, centerY + disY);
					temp.setSymbol('*');
					if (enemyCurBoard->canDrawExplode(temp) && temp != marioPos)
					{
						temp.draw();
					}
				}
			}
		}
		Sleep(SLEEP_DURING_EXPLODE); // Pause before erasing stage 3

		//Then, restores the background that was in the perimeter.
		for (int disX = -2; disX <= 2; ++disX)
		{
			for (int disY = -2; disY <= 2; ++disY)
			{
				if (abs(disX) == 2 || abs(disY) == 2) // Points exactly 2 chars away
				{
					temp.setPointPosition(centerX + disX, centerY + disY);
					temp.setSymbol(enemyCurBoard->getCharFromBoard(centerX + disX, centerY + disY));
					if (enemyCurBoard->canDrawExplode(temp) && temp != marioPos)
					{
						temp.draw();
					}
				}
			}
		}
	}
}
#include "EnemyVEC.h"
EnemyVEC::~EnemyVEC() // EnemyVEC dtor
{
	for (Enemy* enemy : enemysVECTOR)
	{
		delete enemy; // Clean up dynamically allocated memory
	}
}

//Clear enemy vector and insert all ghosts in thier startPos
void EnemyVEC::resetEnemies()
{
	activeBarrelCounter = 0;
	for (Enemy* enemy : enemysVECTOR)
	{
		if (!SilentState::getSilentMode())
		{
			enemy->drawEnemy_Back();
		}
		delete enemy; // Clean up dynamically allocated memory
	}
	enemysVECTOR.clear();

	for (const Point& pos : startPosGhostsVEC)
	{
		if (pos.getSymbol() == Constans::G_SYMBOL)
		{
			Ghost* newGhost = new Ghost(pos, enemyVEC_CurBoard);
			newGhost->SetRandHorizontalDir();
			enemysVECTOR.push_back(newGhost);
		}
		else if (pos.getSymbol() == Constans::SG_SYMBOL)
		{
			SpecialGhost* newSpecialGhost = new SpecialGhost(pos, enemyVEC_CurBoard);
			newSpecialGhost->SetRandHorizontalDir();
			enemysVECTOR.push_back(newSpecialGhost);
		}

	}
}

//Insert new barrel to enemy vector.
void EnemyVEC::AddBarrel()
{
	bool isBarrelStartPosValid;
	if (activeBarrelCounter < MAX_BARRELS_ACTIVE)
	{
		Barrel* newBarrel = new Barrel(enemyVEC_CurBoard, startKong);
		isBarrelStartPosValid = newBarrel->initializeBarrel();
		//Insert newBarrel to vector only if its start position is valid
		if (isBarrelStartPosValid)
		{
			enemysVECTOR.push_back(newBarrel);
			activeBarrelCounter++;
		}
		else
		{
			delete newBarrel;
		}
	}
}


// Draw all active enemies
void EnemyVEC::drawEnemies()
{
		for (Enemy* enemy : enemysVECTOR)
		{
			if (enemy->isEnemyActive())
			{
				enemy->drawEnemy();
			}
		}
}
// Restores the background where the enemies were drawn.
void EnemyVEC::drawBackEnemies()
{
		for (Enemy* enemy : enemysVECTOR)
		{
			if (enemy->isEnemyActive())
			{
				enemy->drawEnemy_Back();
			}
		}
}

// Move all active enemies
void EnemyVEC::moveEnemies()
{
	checkCollisionForTwoGhostsAndFlip();
	for (Enemy* enemy : enemysVECTOR)
	{
		if (enemy->isEnemyActive())
		{
			if (typeid(*enemy) == typeid(Barrel))
			{
				((Barrel*)enemy)->enemyMovement();
			}

			else if (typeid(*enemy) == typeid(Ghost))
			{
				((Ghost*)enemy)->enemyMovement();
			}

			else if (typeid(*enemy) == typeid(SpecialGhost))
			{
				((SpecialGhost*)enemy)->enemyMovement();
			}
		}
	}
}

// Check collision with Mario
bool EnemyVEC::checkCollision(const Point& playerPoint) const
{
	for (Enemy* enemy : enemysVECTOR)
	{
		if (enemy->isEnemyActive() && playerPoint == enemy->getPosition())
		{
			return true;
		}
	}
	return false;
}

// Checks the edge case that mario and enemy switched positions, which mean they should collide.
bool EnemyVEC::isMarioAndEnemySwitchAndHit(const Point& playerPoint, const Point& prevPlayerPoint) const
{
	for (Enemy* enemy : enemysVECTOR)
	{
		if (enemy->isEnemyActive())
		{
			if (enemy->getPrevPosition() == playerPoint && prevPlayerPoint == enemy->getPosition())
			{
				return true;
			}
		}
	}
	return false;
}

// Given mario point, kill every enemy that in range, add proper animation and return how many barrels killed.
int EnemyVEC::handleEnemyStrikedByHammer(const Point& MarioPoint)
{
	int counter = 0;
	for (Enemy* enemy : enemysVECTOR)
	{
		if (enemy->isEnemyActive())
		{
			if ((MarioPoint.getCurX() + MarioPoint.getDirX() == enemy->getPosition().getCurX() || MarioPoint.getCurX() + 2 * MarioPoint.getDirX() == enemy->getPosition().getCurX()) && MarioPoint.getCurY() == enemy->getPosition().getCurY())
			{
				counter++;
				enemy->setIsActive(false);
				if (!SilentState::getSilentMode())
				{
					enemy->drawAnimationKillByHammer();
				}
			}
		}
	}
	return counter;
}


//Remove all inactive enemies.
void EnemyVEC::removeInactive()
{
	for (int i = enemysVECTOR.size() - 1; i >= 0; --i)
	{
		if (!enemysVECTOR[i]->isEnemyActive())
		{
			if (typeid(*(enemysVECTOR[i])) == typeid(Barrel))
			{
				activeBarrelCounter--;
			}
			if (!SilentState::getSilentMode())
			{
				enemysVECTOR[i]->drawEnemy_Back();// Restore background
			}
			delete enemysVECTOR[i];// Free the memory
			enemysVECTOR.erase(enemysVECTOR.begin() + i);// Remove the pointer
		}
	}
}

//Handels barrel explostion and returns if mario hit from the explostion.
bool EnemyVEC::isMarioInExplosionRadius(const Point& marioPosition)
{
	int counter = 0;
	bool isMarioDied = false;
	for (Enemy* enemy : enemysVECTOR)
	{
		// First, we check if enemy is type Barrel and if barel's explode flag is on, activate explode animation and after that set the explode flag to false
		if (typeid(*enemy) == typeid(Barrel) && ((Barrel*)enemy)->isExploded())
		{
			counter++;
			if (!SilentState::getSilentMode())
			{
				((Barrel*)enemy)->ExplodeAnimation(marioPosition);
			}
			((Barrel*)enemy)->setIsActive(false);

			// Then, if mario also 2 chars from the exploded barrel (using custom operator), return true.
			// Else, just reset the barrel and return false
			if (enemy->getPosition() % marioPosition)
			{
				isMarioDied = true;
			}
		}
	}
	return isMarioDied;

}


// Checks if any ghost is going to collide with other ghost,
// and if so flip both of the ghosts directions
void EnemyVEC::checkCollisionForTwoGhostsAndFlip()
{
	for (size_t i = 0; i < enemysVECTOR.size(); ++i)
	{
		// Check if the first object is a Ghost
		if ((typeid(*enemysVECTOR[i]) == typeid(Ghost) || typeid(*enemysVECTOR[i]) == typeid(SpecialGhost)) && enemysVECTOR[i]->isEnemyActive())
		{

			for (size_t j = i + 1; j < enemysVECTOR.size(); ++j)
			{
				// Check if the second object is also a Ghost
				if ((typeid(*enemysVECTOR[j]) == typeid(Ghost) || typeid(*enemysVECTOR[j]) == typeid(SpecialGhost)) && enemysVECTOR[j]->isEnemyActive())
				{

					// Check if the two ghosts are at the same position
					if ((enemysVECTOR[i]->getNextPosition() == enemysVECTOR[j]->getNextPosition()) || (enemysVECTOR[i]->getNextPosition() == enemysVECTOR[j]->getPosition() && enemysVECTOR[j]->getNextPosition() == enemysVECTOR[i]->getPosition()))
					{
						// Flip directions for both
						if (typeid(*enemysVECTOR[i]) == typeid(Ghost))
						{
							static_cast<Ghost*>(enemysVECTOR[i])->flipGhostDir();
						}
						else if (typeid(*enemysVECTOR[i]) == typeid(SpecialGhost))
						{
							static_cast<SpecialGhost*>(enemysVECTOR[i])->flipGhostDir();
						}

						if (typeid(*enemysVECTOR[j]) == typeid(Ghost))
						{
							static_cast<Ghost*>(enemysVECTOR[j])->flipGhostDir();
						}
						else if (typeid(*enemysVECTOR[j]) == typeid(SpecialGhost))
						{
							static_cast<SpecialGhost*>(enemysVECTOR[j])->flipGhostDir();
						}
					}
				}
			}
		}
	}
}



#pragma once
#include "Board.h"
class Enemy
{
protected:
	static constexpr int SLEEP_DURING_HAMMER_KILL_ANIMATION = 70;
	Point p; // Enemy's position.
	bool isActive = true; // Indicates if the enemy is active.
	Board* enemyCurBoard = nullptr; // Pointer to the current game board.

public:
	Enemy(const Point& startPoint = Point(), Board* _board = nullptr) : p(startPoint), enemyCurBoard(_board) {} //Enemy's ctor with start position point

	virtual ~Enemy() {}; // Virtual dtor for enemy.

	Enemy& operator=(const Enemy& other);

	//Pure virtual movement for movement, will be override in ghost, specialGhost and barrel
	virtual void enemyMovement() = 0;

	// Draws the enemy on screen 
	void drawEnemy();

	// Restores the background where the enemy was drawn
	void drawEnemy_Back();

	// Animation when enemy killed by hammer
	void drawAnimationKillByHammer();

	bool isNextEnemyStepValid();

	// Returns the current position of enemy.
	Point getPosition() const
	{
		return p;
	}

	// Gets enemys's next position.
	Point getNextPosition() const
	{
		return Point(p.getCurX() + p.getDirX(), p.getCurY() + p.getDirY());
	}

	// Gets enemy's previous position.
	Point getPrevPosition() const
	{
		return Point(p.getCurX() - p.getDirX(), p.getCurY() - p.getDirY());
	}

	// Sets the current game board pointer.
	void setBoardP(Board* gP)
	{
		enemyCurBoard = gP;
	}

	bool isNextMoveInBounderies()
	{
		Point nextMove(p.getNextMoveX(), p.getNextMoveY());
		return (enemyCurBoard->checkIfIn_X_Boundaries(nextMove) && (enemyCurBoard->checkIfIn_Y_Boundaries(nextMove) || p.getNextMoveY() == Constans::MAX_Y));
	}

	bool isEnemyActive() const
	{
		return isActive;
	}

	void setIsActive(bool activeNew)
	{
		isActive = activeNew;
	}
};


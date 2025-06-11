#pragma once
#include "Enemy.h"
class Ghost : public Enemy
{


	// Variables in order to give to random function to setermine start direction for ghost (LEFT or RIGHT)
	static constexpr int START_LEFT = 0;
	static constexpr int START_RIGHT = 1;

	static constexpr int RANGE_START_CHANGE_DIR = 1; // Start of range to determine possibility of direction change.
	static constexpr int RANGE_END_CHANGE_DIR = 100; // End of range to determine possibility of direction change.
	static constexpr int PROBABILITY_TO_CHANGE_DIR = 5;

	static constexpr int SLEEP_DEATH_BY_HAMMER = 60;

protected:
	// For edge case where ghost is standing on a single floor platform and can't move.
	bool isOnOneFloorFlag = false;

public:
	Ghost(const Point& startPoint = Point(), Board* _board = nullptr) : Enemy(startPoint, _board) {} //Ghost's ctor with start position point



	//Prototypes

	//Sets ghost dir to LEFT or RIGHT randomly (for start or in special ghost when finished climbing).
	void SetRandHorizontalDir();


	// Flip the ghost direction.
	void flipGhostDir();

	// According to assignment's demands, the ghost will change it's direction with the possibility of 5%.
	// The function will determine if change of direction is needed.
	bool isDirectionNeedChange();

	// Handles the ghost's movement and state changes.
	void enemyMovement() override;



};


#pragma once
#include "Ghost.h"
class SpecialGhost : public Ghost
{

	static constexpr int RANGE_START_IF_CLIMBING = 1; // Start of range to determine possibility of climb decision.
	static constexpr int RANGE_END_IF_CLIMBING = 100; // End of range to determine possibility of climb decision.
	static constexpr int PROBABILITY_TO_CLIMB = 15;
	

	bool climbFlag = false;

public:
	SpecialGhost(const Point& startPoint = Point(), Board* _board = nullptr) : Ghost(startPoint, _board) {} //Special Ghost's ctor with start position point

	//Checks if we are in a valid position to climb upwards.
	bool ifCanStartClimbUp();
	//Checks if we are in a valid position to climb downwards.
	bool ifCanStartClimbDown();
	// Handles Special Ghost's climbing upward on ladders.
	void climbUp();
	// Handles Special Ghost's climbing downward on ladders.
	void climbDown();

	// Handles the special ghost's movement and state changes.
	void enemyMovement() override;

	// The function will determine if special ghost should climb, with possibility of 15% to do so.
	bool isStartClimb();

};

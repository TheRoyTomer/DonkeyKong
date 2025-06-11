#pragma once
#include "Enemy.h"
class Barrel : public Enemy
{
	static constexpr int B_FALL_FLOORS_TO_DIE = 8; // Maximum floors the barrel can fall before exploding.
	static constexpr int SLEEP_DURING_EXPLODE = 70; // Sleep time during explosion animation.
	static constexpr int RANGE_START_BARREL_PATH = 1; // Start of range to execute barrel
	static constexpr int RANGE_END_BARREL_PATH = 3; // End of range to execute barrel

	bool isFalling = false; // Indicates if the barrel is falling.
	bool ExplodeFlag = false; // Set to true when the barrel needs to explode.
	int barrelCountLinesFall = 0; // Tracks the number of lines the barrel has fallen.
	int barrelPrevDirX = 0; // Tracks the barrel's previous X direction.

public:
	Barrel(Board* _board = nullptr, const Point& startKongPos = Point()) : Enemy(Point(startKongPos.getCurX(), startKongPos.getCurY(), Constans::B_SYMBOL), _board) {} // Barrel's Ctor.



    // Prototypes
	Barrel& operator=(const Barrel& other);	// Assignment operator for barrels.
    bool initializeBarrel(); // Activates the barrel and sets a random path.
    void changeBarrelDir(int _prevDirX); // Updates the barrel's direction based on the floor type.
    void enemyMovement() override; // Handles the barrel's movement and state changes.
    bool isBarrelFalling() const; // Checks if the barrel is falling.
    void barrelFall(); // Manages the barrel's behavior while falling.
    void ExplodeAnimation(const Point& marioPos); // Animates the barrel's explosion.


	// Checks if the barrel has exploded.
	bool isExploded() const
	{
		return ExplodeFlag;
	}

	

	// Resets the explosion flag to false.
	void setExplodeFlagToFalse()
	{
		ExplodeFlag = false;
	}

	// Sets the barrel's path to the right.
	void setToRightPath()
	{
		p.setPointPosition(p.getCurX() + 1, p.getCurY());
		p.setDirByDirName(Constans::DirNames::RIGHT);
	}

	// Sets the barrel's path to the left.
	void setToLeftPath()
	{
		p.setPointPosition(p.getCurX() - 1, p.getCurY());
		p.setDirByDirName(Constans::DirNames::LEFT);
	}

	// Sets the barrel's path downward - in order to show the explosion.
	void setToDownPath()
	{
		p.setPointPosition(p.getCurX(), p.getCurY() + 2);
		// In order to handle edge case where mario fall and the first floor his falling on is '='.
		// In mario first fall action it takes the dirX to prevDirX, so if mario will land straight on '=' floor
		// It will move left won't stuck
		p.setDirByDirName(Constans::DirNames::LEFT);
	}

};


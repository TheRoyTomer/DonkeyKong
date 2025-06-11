#pragma once
#include "Barrel.h"
#include "SpecialGhost.h"
class EnemyVEC
{
	static constexpr int MAX_BARRELS_ACTIVE = 15; // The maximum amount of active barrels (15).

	int activeBarrelCounter = 0; //Counts the active barrels

	std::vector<Point> startPosGhostsVEC; // Vector with the ghosts and special ghosts start positions.

	Board* enemyVEC_CurBoard = nullptr; // Pointer to the game board, and sets it to null.

	std::vector<Enemy*> enemysVECTOR; // vector that holds all the enemys

	Point startKong; // Position of donkey kong in order to create barrels.

public:
	EnemyVEC(Board* _board = nullptr, Point _startKong = Point(), std::vector<Point> _startPosVEC = {}) : enemyVEC_CurBoard(_board), startKong(_startKong), startPosGhostsVEC(_startPosVEC) {}// enemyVEC ctor
	~EnemyVEC();
    //Clear enemy vector and insert all ghosts in thier startPos
	void resetEnemies();   

	//Insert new barrel to enemy vector.
	void AddBarrel();
	// Draw all active enemies
	void drawEnemies();

	// Restores the background where the enemies were drawn.
	void drawBackEnemies();

	// Move all active enemies
	void moveEnemies();


	// Checks the edge case that mario and enemy switched positions, which mean they should collide.
	bool isMarioAndEnemySwitchAndHit(const Point& playerPoint, const Point& prevPlayerPoint) const;

	// Check collision with Mario
	bool checkCollision(const Point& playerPoint) const;
	
	// Given mario point, kill every enemy that in range, add proper animation and return how many barrels killed.
	int handleEnemyStrikedByHammer(const Point& MarioPoint);

	//Handels barrel explostion and returns if mario hit from the explostion.
	bool isMarioInExplosionRadius(const Point& marioPosition);

	void checkCollisionForTwoGhostsAndFlip();

	//Remove all inactive enemies.
	void removeInactive();    


};


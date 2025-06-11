#include "Enemy.h"


Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		enemyCurBoard = other.enemyCurBoard;
		p = other.p;
		isActive = other.isActive;
	}
	return *this;
}

// Draws the enemy on screen 
void Enemy::drawEnemy()
{
		gotoxy(p.getCurX(), p.getCurY());
		std::cout << p.getSymbol();
}

// Restores the background where the enemy was drawn
void Enemy::drawEnemy_Back()
{
		char prev = enemyCurBoard->getCharFromBoard(p.getCurX(), p.getCurY());
		gotoxy(p.getCurX(), p.getCurY());
		std::cout << prev;
}

void Enemy::drawAnimationKillByHammer()
{
	Point temp = Point(p.getCurX(), p.getCurY(), '*');
	temp.draw();
	Sleep(SLEEP_DURING_HAMMER_KILL_ANIMATION);
	drawEnemy_Back();
}

//Checks the invalid cases where mario's next move is out of bounds, or that his moving Right / Left and his next move is Floor
bool Enemy::isNextEnemyStepValid()
{
	return (isNextMoveInBounderies() && !enemyCurBoard->isOnFloor(Point(p.getNextMoveX(), p.getCurY())));
}
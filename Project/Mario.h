#pragma once
#include "Board.h"
class Mario
{
	static constexpr char movementKeys[] = { 'w', 'a', 'x', 'd', 's' }; // Valid movement keys.
	static constexpr int numKeys = sizeof(movementKeys) / sizeof(movementKeys[0]); // Number of valid keys.
	static constexpr int START_LIFE = 3; // Initial number of lives.
	const int MARIO_MAX_FLOORS_TO_FALL = 5; // Maximum floors Mario can fall before dying.
	const int EXPLODE_ITERATIONS = 3; // Number of iterations explode animation doing
	const int SLEEP_EXPLODE_ANIMATION = 200;

	int prevDirX = 0; // Previous horizontal direction.
	bool fallFlag = false; // Indicates if Mario is falling.
	bool jumpFlag = false; // Indicates if Mario is jumping.
	bool climbFlag = false; // Indicates if Mario is climbing.

	bool isHoldingHammer = false; // Indicates if Mario holding hammer

	int jumpStep = 0; // Tracks steps during a jump.
	int countFallFloors = 0; // Counts the number of floors Mario has fallen.
	int curLife = START_LIFE; // Current number of lives.
	Point p; // Position of Mario.
	Board* curBoard = nullptr; // Pointer to the game board.
	//Point startPos;


public:
	// Mario's Ctor, initializing Mario's position, lives, and the game board.
	Mario(Board* _board = nullptr, const Point& startPos = Point()) : curBoard(_board), p(Point(startPos.getCurX(), startPos.getCurY(), Constans::M_SYMBOL)) {}


	//Prototypes
	bool validKey(const char key) const; // Checks if key pressed is 'a' or 's' or 'd' or 'w' or 'x' or 'p'
	bool validMovementKey(const char key) const; // Checks if a key press corresponds to a valid move.
	void keyPressed(char key); // Processes a valid key press to adjust Mario's direction.
	bool checkNextStepValid(); // Validates if the next step is within bounds.
	bool marioMovement(); // Handles Mario's movement, including jumping and falling. returns true if mario died by falling.
	void climbUp(); // Handles Mario climbing up ladders.
	void climbDown(); // Handles Mario climbing down ladders.
	void jump(); // Handles Mario's jumping behavior.
	bool marioFall(); // Handles Mario's falling behavior and checks for death.
	void handleStrike(); // Handles Mario losing a life after a strike.
	void resetMarioMembers(); // Change all mario's data members to thier initial state.
	void strikeAnimation(); // Plays an animation when Mario is struck.

	// Draws Mario on the screen.
	void drawM()
	{
		gotoxy(p.getCurX(), p.getCurY());
		std::cout << Constans::M_SYMBOL;
	}

	// Restores the background character behind Mario.
	void drawM_Back()
	{
		char prev = curBoard->getCharFromBoard(p.getCurX(), p.getCurY());
		gotoxy(p.getCurX(), p.getCurY());
		std::cout << prev;
	}

	// Return if holding hammer.
	bool getIsHoldingHammer() const
	{
		return isHoldingHammer;
	}

	void setToHoldHammer()
	{
		isHoldingHammer = true;
	}
	// Gets Mario's current position.
	Point getMarioPos() const
	{
		return p;
	}

	// Gets Mario's previous position.
	Point getMarioPrevPos() const
	{
		return Point(p.getCurX() - p.getDirX(), p.getCurY() - p.getDirY());
	}

	// Gets Mario's next position.
	Point getMarioNextPos() const
	{
		return Point(p.getCurX() + p.getDirX(), p.getCurY() + p.getDirY());
	}

	// Returns Mario's current life count.
	int getCurLife() const
	{
		return curLife;
	}

	// Sets remaining lives to 3.
	void setToStartLife()
	{
		curLife = START_LIFE;
	}

	// Sets mario position when level starts.
	void setMarioStartPos(const Point& marioNewPos)
	{
		p.setPointPosition(marioNewPos.getCurX(), marioNewPos.getCurY());
	}
};



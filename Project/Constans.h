#pragma once
class Constans
{

public:

	// Represents the screen size.
	static constexpr int MAX_X = 80; 
	static constexpr int MAX_Y = 25;

	// enum to represent keys and directions names for clarity 
	enum class DirNames { UP = 0, LEFT, DOWN, RIGHT, STAY };

	//Symbols for objects
	static constexpr char B_SYMBOL = 'O'; // Symbol representing the barrel.
	static constexpr char G_SYMBOL = 'x'; // Symbol representing the barrel.
	static constexpr char SG_SYMBOL = 'X'; // Symbol representing the special ghost.
	static constexpr char M_SYMBOL = '@'; // Symbol representing Mario.
	static constexpr char HAMMER_SYMBOL = 'p'; // Symbol representing Hammer.
	static constexpr char PLUS_SYMBOL = '+'; // Symbol representing plus element (bonus section in project).

};


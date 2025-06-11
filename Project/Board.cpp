#include "Board.h"

// Function to load a screen from file.
bool Board::load(const std::string& fileName)
{
	//Reset Plus Point to the default state indicating that there aren't any + in screen
	startPlus = Point(-1, -1);
	// Boolians flags to mark invalid boards.
	bool kongFlag = false, paulineFlag = false, marioFlag = false, hammerFlag = false, lFlag = false, isFloorBelowPauline = false, plusFlag = false;
	bool isFloorBelowGhosts = true;
	std::ifstream file(fileName);
	int lineCounter = 0, charCounter;
	char ch;
	startGhostsVEC.clear();
	// If the file was opened successfully, start loading.
	if (file.is_open())
	{
		// Iterate through the lines - stops at line 24 or at end of file.
		while (lineCounter < Constans::MAX_Y &&!file.eof())
		{
			charCounter = 0;
			// Read by character until MAX_X or reaching end of line.
			// For every object read replace it with ' ' and set his start position with our first incounter with the object symbole.
			while (file.get(ch) && charCounter < Constans::MAX_X && ch != '\n' && ch != '\0')
			{
				switch (ch)
				{
				case Constans::M_SYMBOL:
					if (!marioFlag)
					{
						startMario = Point(charCounter, lineCounter);
						marioFlag = true;
					}
					ch = ' ';
					break;

				case BOUNDERIES_SYMBOL:
					ch = ' ';
					break;

				case KONG_SYMBOL:
					if (!kongFlag)
					{
						startKong = Point(charCounter, lineCounter);
						kongFlag = true;
					}
					else
					{
						ch = ' ';
					}
					break;

				case PAULINE_SYMBOL:
					if (!paulineFlag)
					{
						startPauline = Point(charCounter, lineCounter);
						paulineFlag = true;
					}
					else
					{
						ch = ' ';
					}
					break;

				case Constans::G_SYMBOL:
					startGhostsVEC.push_back(Point(charCounter, lineCounter, Constans::G_SYMBOL));
					ch = ' ';
					break;

				case Constans::SG_SYMBOL:
					startGhostsVEC.push_back(Point(charCounter, lineCounter, Constans::SG_SYMBOL));
					ch = ' ';
					break;
				

				case HUD_EDGE_SYMBOL:
					if (!lFlag)
					{
						startL = Point(charCounter, lineCounter);
						lFlag = true;
					}
					ch = ' ';
					break;

				case Constans::PLUS_SYMBOL:
					if (!plusFlag)
					{
						startPlus = Point(charCounter, lineCounter, Constans::PLUS_SYMBOL);
						plusFlag = true;
					}
					else
					{
						ch = ' ';
					}
					break;
				case Constans::HAMMER_SYMBOL: case 'P':
					if (!hammerFlag)
					{
						startHammer = Point(charCounter, lineCounter, Constans::HAMMER_SYMBOL);
						hammerFlag = true;
					}
					else
					{
						ch = ' ';
					}
					break;
				default:
					if (!isLadder(ch) && !isFloor(ch))
					{
						ch = ' ';
					}
					break;
				}
				curBoard[lineCounter][charCounter] = ch; // Insert the character to the array.
				charCounter++;
			}
			// If the line is less then 80 characters, fill the remaining space with ' '.
			while (charCounter < Constans::MAX_X)
			{
				curBoard[lineCounter][charCounter] = ' ';
				charCounter++;
			}
			curBoard[lineCounter][Constans::MAX_X] = '\0';

			// If the line is more then 80 characters, we'll read through them to move forward.
			while (ch != '\n' && file.get(ch))
			{
				charCounter++;
			}
			lineCounter++;
		}
		// If the file is less then 25 rows, fill the remaining space with lines full of ' '.
		while (lineCounter < Constans::MAX_Y)
		{
			for (int i = 0; i < Constans::MAX_X; i++)
			{
				curBoard[lineCounter][i] = ' ';
			}
			curBoard[lineCounter][Constans::MAX_X] = '\0';
			lineCounter++;
		}
		// Close the file.
		file.close();

		// Check if Pauline is standing on a floor.
		isFloorBelowPauline = isFloorBelow(startPauline);

		// Check if all the ghosts are standing on a floor.
		for (int i = 0; i < startGhostsVEC.size(); i++)
		{
			if (!isFloorBelow(startGhostsVEC[i]))
			{
				isFloorBelowGhosts = false;
			}
		}
		// Returns if the file is valid.
		return kongFlag && paulineFlag && hammerFlag && marioFlag && lFlag && isFloorBelowPauline && isFloorBelowGhosts;
	}
	// If the file couldn't open - he is invalid. 
	else
	{
		return false;
	}

}

void Board::present()
{
	if (!SilentState::getSilentMode())
	{
		clearScreen();
		gotoxy(0, 0);
		// Copy the predefined game level to the current board and display it.
		for (int i = 0; i < Constans::MAX_Y; i++)
		{
			if (i != Constans::MAX_Y - 1)
			{
				std::cout << curBoard[i] << '\n';
			}
		}
		std::cout << curBoard[Constans::MAX_Y - 1];
	}
}


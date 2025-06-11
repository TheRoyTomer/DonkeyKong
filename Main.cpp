//#include "Game.h"
#include "GameSaveAndRegMode.h"
#include "GameLoadMode.h"

int main(int argc, char** argv)
{
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	Game* gPtr = nullptr;
	if (isLoad)
	{
		gPtr = new GameLoadMode(isSilent);
	}
	else
	{
		//If here isSave is false, and isLoad is false as well, then GameSaveAndRegMode ctor parameter is false, indicating regular mode.
		gPtr = new GameSaveAndRegMode(isSave);
	}

	if (gPtr)
	{
		gPtr->RunGame();
		delete gPtr;
	}
	return 0;
}

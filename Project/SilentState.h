#pragma once

//Class that handles static variable for silent mode, in order that many classes (EnemyVEC, HUD, Board,Game) will now if they should display or print.
class SilentState
{
private:
    static bool isSilent; 

public:
    //Change Silent mode to true
    static void setToSilentMode()
    {
        isSilent = true;
    }

    //Gets the Silent mode state
    static bool getSilentMode()
    {
        return isSilent;
    }
};


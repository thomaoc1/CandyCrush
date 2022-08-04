#ifndef GAME_OBJECTIVE_HPP
#define GAME_OBJECTIVE_HPP

#include "../constants/constants.hpp"
#include "filehandler/gameData.hpp"
#include "../view/gridDisplay.hpp"

class GameObjective {
    int objType;
    int nSwaps;
    int obj;
    int colour = 0;

    GridDisplay &observer;

    enum{LOST, WON, ONGOING};

public:
    GameObjective(const GameData &gd, GridDisplay &observer);
    GameObjective(const GameObjective &) = default;
    GameObjective(GameObjective &&) = default;
    
    int gameState() const;

    int swaps() const {return nSwaps;}

    void swapped();
    void ingredientPop();
    void frostingPop();
    void colourPop(int colour);
};


#endif
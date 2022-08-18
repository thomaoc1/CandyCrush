#ifndef GAME_OBJECTIVE_HPP
#define GAME_OBJECTIVE_HPP

#include "../common/constants.hpp"
#include "filehandler/gameData.hpp"
#include "../view/gridDisplay.hpp"

class GameObjective {
    int objType;
    int nSwaps;
    int obj;
    int colour = 0;

    GridDisplay &observer;

public:
    GameObjective(const GameData &gd, GridDisplay &observer) : observer{observer} {gameDataInter(gd);}
    GameObjective(GridDisplay &observer) : observer{observer} {}
    GameObjective(const GameObjective &) = default;
    GameObjective(GameObjective &&) = default;
    
    void setGameData(const GameData &gd) {gameDataInter(gd);}
    int gameState() const;
    int swaps() const {return nSwaps;}

    void swapped();
    void ingredientPop();
    void frostingPop();
    void colourPop(int colour);

private:
    void gameDataInter(const GameData &gd);
};


#endif
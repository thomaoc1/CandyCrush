#ifndef GAME_OBJECTIVE_HPP
#define GAME_OBJECTIVE_HPP

#include "../constants/constants.hpp"
#include "filehandler/gameData.hpp"

class GameObjective {
    int objType;
    int nSwaps;
    int obj;
    int colour = 0;
    enum{LOST, WON, ONGOING};

public:
    GameObjective(const GameData &gd);
    GameObjective(const GameObjective &) = default;
    GameObjective(GameObjective &&) = default;
    
    int gameState() const;

    void swapped() {--nSwaps;}
    void cherryPop() {if (objType == Constants::CHERRIES) --obj;}
    void hazelPop() {if (objType == Constants::HAZELNUT) --obj;}
    void frostingPop() {if (objType == Constants::FROSTINGS) --obj;}
    void colourPop(int colour);
};


#endif
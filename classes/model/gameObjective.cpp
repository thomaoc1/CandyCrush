#include "gameObjective.hpp"


GameObjective::GameObjective(const GameData &gd) : nSwaps{gd.maxSwaps} {
    for (int i = 0; i < static_cast<int>(gd.objTypes.size()); ++i)
        if (gd.objTypes[i]) objType = i;

    obj = gd.objectives[objType];
    if (objType == Constants::POPS) colour = gd.colour;
}


int GameObjective::gameState() const {
    if (nSwaps <= 0) return LOST;
    else if (obj <= 0) return WON;

    return ONGOING;
}
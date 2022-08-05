#include "gameObjective.hpp"


GameObjective::GameObjective(const GameData &gd, GridDisplay &observer) : nSwaps{gd.maxSwaps}, observer{observer} {
    for (int i = 0; i < static_cast<int>(gd.objTypes.size()); ++i)
        if (gd.objTypes[i]) objType = i;

    obj = gd.objectives[objType];
    if (objType == Constants::POPS) colour = gd.colour;

    observer.notifySwapsLeft(nSwaps);
    if (objType == Constants::POPS) observer.notifyObjective(objType, obj, colour);
    else observer.notifyObjective(objType, obj);
}


int GameObjective::gameState() const {
    int gamestate = ONGOING;
    if (nSwaps <= 0) gamestate = LOST;
    else if (obj <= 0) gamestate = WON;
    return gamestate;
}


void GameObjective::swapped() {
    --nSwaps;
    observer.notifySwapsLeft(nSwaps);
    observer.notifyGameState(gameState());
}


void GameObjective::ingredientPop() {
    if (objType == Constants::INGREDIENT) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


void GameObjective::frostingPop() {
    if (objType == Constants::FROSTINGS) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


void GameObjective::colourPop(int poppedColour) {
    if (objType == Constants::POPS && colour == poppedColour && obj > 0) {
        --obj;
        observer.notifyObjective(objType, obj, colour);
        observer.notifyGameState(gameState());
    }
}
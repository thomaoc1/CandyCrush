#include "gameObjective.hpp"


GameObjective::GameObjective(const GameData &gd, GridDisplay &observer) : nSwaps{gd.maxSwaps}, observer{observer} {
    for (int i = 0; i < static_cast<int>(gd.objTypes.size()); ++i)
        if (gd.objTypes[i]) objType = i;

    obj = gd.objectives[objType];
    if (objType == Constants::POPS) colour = gd.colour;

    observer.notifySwapsLeft(nSwaps);
}


int GameObjective::gameState() const {
    if (nSwaps <= 0) return LOST;
    else if (obj <= 0) return WON;

    return ONGOING;
}


void GameObjective::swapped() {
    --nSwaps;
    observer.notifySwapsLeft(nSwaps);
    observer.notifyGameState(gameState());
}


void GameObjective::ingredientPop() {
    if (objType == Constants::INGREDIENT) {
        --obj;
        // observer.objectivePop();
        observer.notifyGameState(gameState());
    }
}


void GameObjective::frostingPop() {
    if (objType == Constants::FROSTINGS) {
        --obj;
        // observer.objectivePop();
        observer.notifyGameState(gameState());
    }
}


void GameObjective::colourPop(int poppedColour) {
    if (objType == Constants::POPS && colour == poppedColour) {
        --obj;
        // observer.objectivePop();
        observer.notifyGameState(gameState());
    }
}
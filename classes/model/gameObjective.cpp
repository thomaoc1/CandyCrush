#include "gameObjective.hpp"


/**
 * @brief 
 * 
 * @param gd 
 */
void GameObjective::gameDataInter(const GameData &gd) {

    nSwaps = gd.maxSwaps;

    for (int i = 0; i < static_cast<int>(gd.objTypes.size()); ++i)
        if (gd.objTypes[i]) objType = i;

    obj = gd.objectives[objType];
    colour = gd.colour;

    observer.notifySwapsLeft(nSwaps);
    if (objType == Constants::POPS) observer.notifyObjective(objType, obj, colour);
    else observer.notifyObjective(objType, obj);
}


/**
 * @brief 
 * 
 * @return int 
 */
GameState GameObjective::gameState() const {
    GameState gamestate = GameState::ONGOING;
    if (nSwaps <= 0) gamestate = GameState::LOST;
    else if (obj <= 0) gamestate = GameState::WON;
    return gamestate;
}


/**
 * @brief 
 * 
 */
void GameObjective::swapped() {
    --nSwaps;
    observer.notifySwapsLeft(nSwaps);
    observer.notifyGameState(gameState());
}


/**
 * @brief 
 * 
 */
void GameObjective::ingredientPop() {
    if (objType == Constants::INGREDIENT) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


/**
 * @brief 
 * 
 */
void GameObjective::frostingPop() {
    if (objType == Constants::FROSTINGS) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


/**
 * @brief 
 * 
 * @param poppedColour 
 */
void GameObjective::colourPop(Colour poppedColour) {
    if (objType == Constants::POPS && colour == poppedColour && obj > 0) {
        --obj;
        observer.notifyObjective(objType, obj, colour);
        observer.notifyGameState(gameState());
    }
}
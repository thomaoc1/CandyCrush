#include "gameObjective.hpp"


/**
 * @brief Interprets GameData struct
 * 
 * @param gd 
 */
void GameObjective::gameDataInter(const GameData &gd) {

    nSwaps = gd.maxSwaps;
    objType = gd.objType;
    obj = gd.objective;
    colour = gd.colour;

    observer.notifySwapsLeft(nSwaps);
    if (objType == ObjectiveType::POPS) observer.notifyObjective(objType, obj, colour);
    else observer.notifyObjective(objType, obj);
}


/**
 * @brief Deduces game state
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
 * @brief Swapping handler
 * 
 */
void GameObjective::swapped() {
    --nSwaps;
    observer.notifySwapsLeft(nSwaps);
    observer.notifyGameState(gameState());
}


/**
 * @brief Ingredient pop objective tracker
 * 
 */
void GameObjective::ingredientPop() {
    if (objType == ObjectiveType::INGREDIENT) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


/**
 * @brief Frosting pop objective tracker
 * 
 */
void GameObjective::frostingPop() {
    if (objType == ObjectiveType::FROSTINGS) {
        --obj;
        observer.notifyObjective(objType, obj);
        observer.notifyGameState(gameState());
    }
}


/**
 * @brief Colour pop objective tracker
 * 
 * @param poppedColour 
 */
void GameObjective::colourPop(Colour poppedColour) {
    if (objType == ObjectiveType::POPS && colour == poppedColour && obj > 0) {
        --obj;
        observer.notifyObjective(objType, obj, colour);
        observer.notifyGameState(gameState());
    }
}
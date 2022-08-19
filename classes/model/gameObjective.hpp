/**
 * @file gameObjective.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of tracking the progress towards
 *  winning / losing the game.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef GAME_OBJECTIVE_HPP
#define GAME_OBJECTIVE_HPP

#include "../common/constants.hpp"
#include "../filehandler/gameData.hpp"
#include "../view/gridDisplay.hpp"

class GameObjective {
    ObjectiveType objType;
    Colour colour;
    int nSwaps;
    int obj;
    GridDisplay &observer;

public:
    GameObjective(const GameData &gd, GridDisplay &observer) : observer{observer} {gameDataInter(gd);}
    GameObjective(GridDisplay &observer) : observer{observer} {}
    GameObjective(const GameObjective &) = default;
    GameObjective(GameObjective &&) = default;
    
    void setGameData(const GameData &gd) {gameDataInter(gd);}
    GameState gameState() const;
    int swaps() const {return nSwaps;}

    void swapped();
    void ingredientPop();
    void frostingPop();
    void colourPop(Colour colour);

private:
    void gameDataInter(const GameData &gd);
};


#endif
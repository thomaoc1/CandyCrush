/**
 * File : 
 *  gameData.hpp
 *
 * Decription :
 *  Struct which holds all data to start a game.
 * 
 * Dependencies :
 *  point.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP 

#include <vector>
#include "../../shared/point.hpp"

struct GameData {
    std::vector<Point> walls;
    std::vector<Point> frostings; 
};


#endif
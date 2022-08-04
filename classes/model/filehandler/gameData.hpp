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
#include <array>
#include "../../shared/point.hpp"

struct GameData {
    int maxSwaps;
    std::array<bool, 3> objTypes = {false, false, false};
    std::array<int, 3> objectives = {0, 0, 0};
    int colour = 0;
    using CoordType = std::pair< Point, int >;
    std::vector<CoordType> components;
    
};


#endif
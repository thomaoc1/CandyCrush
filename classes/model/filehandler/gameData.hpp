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
#include "../../common/enumerations.hpp"
#include "../../common/componentType.hpp"

struct GameData {
    int maxSwaps;
    ObjectiveType objType;
    int objective;
    Colour colour;
    using CoordType = std::pair< Point, ComponentType >;
    std::vector<CoordType> components;
};


#endif
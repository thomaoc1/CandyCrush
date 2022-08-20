/**
 * @file gameData.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Struct used to store game data.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP 

#include <vector>
#include <array>
#include "../common/point.hpp"
#include "../common/enumerations.hpp"
#include "../common/componentType.hpp"

struct GameData {
    int maxSwaps;
    ObjectiveType objType;
    int objective;
    Colour colour;
    using CoordType = std::pair< Point, ComponentType >;
    std::vector<CoordType> components;
};


#endif
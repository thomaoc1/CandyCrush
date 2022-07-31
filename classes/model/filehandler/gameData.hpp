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
    std::vector<Point> candies;
    std::vector<Point> walls;
    std::vector<Point> frostings; 
    std::vector<Point> cherries;
    std::vector<Point> hazels;
    std::vector<Point> wrapped;
    std::vector<Point> striped;
    std::vector<Point> special;
};


#endif
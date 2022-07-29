/**
 * File : 
 *  wall.hpp
 *
 * Decription :
 *  Class which represents a specific GameComponent ; "Wall"
 * 
 * Dependencies : 
 *  gameComponent.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef WALL_HPP
#define WALL_HPP

#include "gameComponent.hpp"

class Wall : public GameComponent {
public:
    int type() const override {return Constants::WALL;}
    std::string toString() const override {return "#";}
};

#endif
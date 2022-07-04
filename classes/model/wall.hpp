/**
 * File : 
 *  wall.hpp
 *
 * Decription :
 *  Class which represents a specific GameComponent ; "Wall"
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
    const std::string package() const override {return Constants::WALL;};
};

#endif
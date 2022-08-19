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
    Wall() : GameComponent{ComponentType{Colour::BLACK, Component::WALL}, BlastType::NO_BLAST, Direction::NO_DIRECTION} {}
    ComponentType type() const override {return ComponentType{Colour::BLACK, Component::WALL};}
};

#endif
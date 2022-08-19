/**
 * @file wall.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a Wall component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef WALL_HPP
#define WALL_HPP

#include "gameComponent.hpp"

class Wall : public GameComponent {
public:
    Wall() : GameComponent{ComponentType{Colour::BLACK, Component::WALL}} {}
};

#endif
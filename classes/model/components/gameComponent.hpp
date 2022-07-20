/**
 * File : 
 *  gameComponent.hpp
 *
 * Decription :
 *  Interface which describes the behavior of GameComponents
 * 
 * Authors:
 *  Thomas O'Cuilleanain
 *  Marcus Chretien
 */

#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "../../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
    const int colour;
public:
    GameComponent(int colour) : colour{colour} {}
    GameComponent() : colour{Constants::components::NONE} {}
    virtual ~GameComponent() {};
    virtual int getColour() const {return colour;}
    virtual int type() const=0;
};

#endif
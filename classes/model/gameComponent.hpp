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

#include "../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
    std::string colour;
public:
    GameComponent(const std::string &colour) : colour{colour} {}
    GameComponent() : colour{Constants::NONE} {}
    virtual ~GameComponent() {};
    virtual const std::string getColour() const {return colour;}
    virtual const std::string package() const=0;
};

#endif
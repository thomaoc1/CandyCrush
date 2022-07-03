/**
 * File : 
 *  gameComponent.hpp
 *
 * Decription :
 *  Interface which describes the behavior of GameComponents
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
public:
    virtual ~GameComponent() {};
    virtual std::string package() const=0;
};

#endif
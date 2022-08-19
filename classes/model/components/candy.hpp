/**
 * File : 
 *  candy.hpp
 * 
 * Description : 
 *  Class which represents a specific GameComponent ; "Candy".
 * 
 * Dependencies :
 *  gameComponent.hpp
 * 
 * Authors : 
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef CANDY_HPP
#define CANDY_HPP

#include "gameComponent.hpp"

class Candy : public GameComponent {
public:
    Candy() noexcept
        : GameComponent(ComponentType{Constants::randomColour(), Component::CANDY}) {}
    Candy(Colour colour) noexcept
        : GameComponent(ComponentType{colour, Component::CANDY}) {}
    virtual ~Candy() = default;
};

#endif
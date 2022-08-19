/**
 * @file candy.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a Candy component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef CANDY_HPP
#define CANDY_HPP

#include "gameComponent.hpp"

class Candy : public GameComponent {
public:
    Candy() noexcept
        : GameComponent(ComponentType{randomColour(), Component::CANDY}) {}
    Candy(Colour colour) noexcept
        : GameComponent(ComponentType{colour, Component::CANDY}) {}
};

#endif
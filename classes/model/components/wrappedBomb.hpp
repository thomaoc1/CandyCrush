/**
 * @file wrappedBomb.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a WrappedBomb component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef WRAPPED_BOMB_HPP
#define WRAPPED_BOMB_HPP

#include "gameComponent.hpp"

class WrappedBomb : public GameComponent {
public:
    WrappedBomb(Colour colour) noexcept
        : GameComponent(ComponentType{colour, Component::WRAPPED_BOMB}) {}
    WrappedBomb() noexcept
        : GameComponent(ComponentType{randomColour(), Component::WRAPPED_BOMB}) {}
                         
    WrappedBomb(const WrappedBomb &) = default;
    WrappedBomb(WrappedBomb &&) = default;    
};

#endif
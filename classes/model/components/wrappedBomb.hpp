/**
 * File : 
 *  wrappedBomb.hpp
 * 
 * Description : 
 *  Class which represents a specific GameComponent ; "Wrapped Candy Bomb".
 * 
 * Dependencies:
 *  candy.hpp
 * 
 * Authors : 
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef WRAPPED_BOMB_HPP
#define WRAPPED_BOMB_HPP

#include "gameComponent.hpp"

class WrappedBomb : public GameComponent {
public:
    WrappedBomb(Colour colour) noexcept
        : GameComponent(ComponentType{colour, Component::WRAPPED_BOMB}, BlastType::WRAPPED, Direction::NO_DIRECTION) {}
    WrappedBomb() noexcept
        : GameComponent(ComponentType{randomColour(), Component::WRAPPED_BOMB}, 
                         BlastType::WRAPPED, Direction::NO_DIRECTION) {}
                         
    WrappedBomb(const WrappedBomb &) = default;
    WrappedBomb(WrappedBomb &&) = default;    
};

#endif
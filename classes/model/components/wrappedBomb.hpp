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
    WrappedBomb(int colour) noexcept : GameComponent(colour, Constants::WRAPPED, Constants::NO_DIRECTION) {}
    WrappedBomb() noexcept : GameComponent(Constants::randomCandy(), Constants::WRAPPED, Constants::NO_DIRECTION) {}
    WrappedBomb(const WrappedBomb &) = default;
    WrappedBomb(WrappedBomb &&) = default;
    
    int type() const override {return Constants::colourToWr(getColour());}
    std::string toString() const override {return GameComponent::toString() + "Wr";}
};

#endif
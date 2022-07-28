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
    Candy() noexcept : GameComponent(Constants::randomCandy(), 1, Constants::NO_DIRECTION) {}
    Candy(int colour) noexcept : GameComponent(colour, 1, Constants::NO_DIRECTION) {}
    virtual ~Candy() = default;
    virtual int type() const override {return getColour();}
};

#endif
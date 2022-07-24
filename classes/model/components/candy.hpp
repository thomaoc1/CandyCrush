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
    Candy() : GameComponent(Constants::randomCandy(), 1, Constants::NO_DIRECTION) {}
    Candy(int colour) : GameComponent(colour, 1, Constants::NO_DIRECTION) {}
    virtual ~Candy() {}
    virtual int type() const override {return getColour();}
};

#endif
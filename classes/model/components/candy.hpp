/**
 * File : 
 *  candy.hpp
 * 
 * Description : 
 *  Class which represents a specific GameComponent ; "Candy".
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
    Candy() : GameComponent(Constants::randomCandy()) {}
    Candy(int colour) : GameComponent(colour) {}
    virtual ~Candy() {}
    virtual int type() const override {return getColour();};
};

#endif
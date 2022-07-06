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
    Candy(std::string colour) : GameComponent(colour) {}
    virtual ~Candy() {}
    virtual const std::string package() const override {return GameComponent::getColour();} 
};

#endif
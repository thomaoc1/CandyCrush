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
    std::string colour;
public:
    Candy() : GameComponent(), colour{Constants::randomCandy()} {}
    Candy(std::string colour) : GameComponent(), colour{colour} {}
    virtual ~Candy() {}
    virtual std::string package() const override {return colour;} 
};

#endif
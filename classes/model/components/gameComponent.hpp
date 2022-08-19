/**
 * File : 
 *  gameComponent.hpp
 *
 * Decription :
 *  Interface which describes the behavior of GameComponents
 * 
 * Dependencies:
 *  constants.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain
 *  Marcus Chretien
 */

#ifndef GAMECOMPONENT_HPP
#define GAMECOMPONENT_HPP

#include "../../common/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
    const int colour;
    const int blastType;
    const Direction blastDirection;
public:
    GameComponent(int colour, int blastType, Direction blastDirection) noexcept 
        : colour{colour}, blastType{blastType}, blastDirection{blastDirection} {}
    GameComponent(int colour) noexcept
        : colour{colour}, blastType{Constants::SIMPLE}, blastDirection{Constants::NO_DIRECTION} {}
    GameComponent() noexcept 
        : colour{Constants::NONE}, blastType{Constants::SIMPLE}, blastDirection{Constants::NO_DIRECTION} {}
    virtual ~GameComponent() = default;

    virtual int pop() {return Constants::POPPED;}
    virtual int getColour() const {return colour;}
    virtual int getBlastType() const {return blastType;}
    virtual Direction getBlastDirection() const {return blastDirection;}
    virtual void explode() {}
    virtual int type() const=0;


    // Logging
    virtual std::string toString() const;
};

#endif
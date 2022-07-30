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

#include "../../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
    const int colour;
    const int blastType;
    const int blastDirection;
public:
    GameComponent(int colour, int blastType, int blastDirection) noexcept 
        : colour{colour}, blastType{blastType}, blastDirection{blastDirection} {}
    GameComponent(int colour) noexcept
        : colour{colour}, blastType{Constants::SIMPLE}, blastDirection{Constants::NO_DIRECTION} {}
    GameComponent() noexcept 
        : colour{Constants::NONE}, blastType{Constants::SIMPLE}, blastDirection{Constants::NO_DIRECTION} {}
    virtual ~GameComponent() = default;

    virtual int getColour() const {return colour;}
    virtual int getBlastType() const {return blastType;}
    virtual int getBlastDirection() const {return blastDirection;}
    virtual int type() const=0;


    // Logging
    virtual std::string toString() const;
};

#endif
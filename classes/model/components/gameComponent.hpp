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
    const int blastArea;
    const int blastDirection;
public:
    GameComponent(int colour, int blastArea, int blastDirection) noexcept : colour{colour}, 
                                                                            blastArea{blastArea}, 
                                                                            blastDirection{blastDirection} {}
    GameComponent() noexcept : colour{Constants::NONE}, blastArea{0}, blastDirection{Constants::NO_DIRECTION} {}
    virtual ~GameComponent() = default;
    virtual int getColour() const {return colour;}
    virtual int getBlastArea() const {return blastArea;}
    virtual int getBlastDirection() const {return blastDirection;}
    virtual int type() const=0;


    virtual std::string toString() const {
        std::string ret;
        switch (colour) {
            case Constants::RED:
                ret = "R";
                break; 
            case Constants::BLUE:
                ret = "B";
                break;
            case Constants::GREEN:
                return "G";
                break;
            case Constants::PURPLE:
                ret = "P";
                break;
            case Constants::YELLOW:
                ret = "Y";
                break;
            case Constants::ORANGE:
                ret = "O";
                break;
            case Constants::WALL:
                ret = "#";
                break;
        }
        return ret;
    }
};

#endif
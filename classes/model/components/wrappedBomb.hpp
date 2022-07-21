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

#include "candy.hpp"

class WrappedBomb : public Candy {
public:
    WrappedBomb(int colour) : Candy(colour) {}
    WrappedBomb() : Candy(Constants::randomCandy()) {}
    int type() const override;
};

#endif
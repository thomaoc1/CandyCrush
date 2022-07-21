/**
 * File : 
 *  stripedBomb.hpp
 * 
 * Description : 
 *  Class which represents a specific GameComponent ; "Striped Candy Bomb".
 * 
 * Dependencies:
 *  candy.hpp
 * 
 * Authors : 
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef STRIPED_BOMB_HPP
#define STRIPED_BOMB_HPP

#include "candy.hpp"

class StripedBomb : public Candy {
public:
    StripedBomb(int colour) : Candy(colour) {}
    StripedBomb() : Candy(Constants::randomCandy()) {}
    int type() const override;
};

#endif
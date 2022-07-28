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

#include "gameComponent.hpp"

class StripedBomb : public GameComponent {
public:
    StripedBomb(int colour, int blastDirection) noexcept : GameComponent(colour, 1, blastDirection) {}
    StripedBomb() noexcept : GameComponent(Constants::randomCandy(), 1, Constants::randomDirection()) {}
    int type() const override;
};

#endif
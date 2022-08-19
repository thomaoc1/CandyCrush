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
    StripedBomb(Colour colour, Direction blastDirection) noexcept
        : GameComponent(ComponentType{colour, Constants::directionToSt(blastDirection)}, BlastType::STRIPED, blastDirection) {}
    StripedBomb() noexcept 
        : GameComponent(ComponentType{Constants::randomColour(), 
                                       Constants::directionToSt(Constants::randomDirection())}, 
                                       BlastType::STRIPED, Constants::randomDirection()) {}
    StripedBomb(const StripedBomb &) = default;
    StripedBomb(StripedBomb &&) = default;
};

#endif
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
    StripedBomb(int colour, int blastDirection) noexcept : GameComponent(colour, Constants::STRIPED, blastDirection) {}
    StripedBomb() noexcept : GameComponent(Constants::randomCandy(), Constants::STRIPED, Constants::randomDirection()) {}
    StripedBomb(const StripedBomb &) = default;
    StripedBomb(StripedBomb &&) = default;

    int type() const override {return Constants::colourToSt(getColour(), getBlastDirection());};

    std::string toString() const override {
        std::string direction = getBlastDirection() == Constants::VERTICAL ? "V" : "H";
        return GameComponent::toString() + "St" + direction;
    } 
};

#endif
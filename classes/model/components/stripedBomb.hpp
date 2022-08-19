/**
 * @file stripedBomb.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a StripedBomb component
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef STRIPED_BOMB_HPP
#define STRIPED_BOMB_HPP

#include "gameComponent.hpp"

class StripedBomb : public GameComponent {
public:
    StripedBomb(Colour colour, Direction blastDirection) noexcept
        : GameComponent(ComponentType{colour, Constants::directionToSt(blastDirection)}) {}
    StripedBomb() noexcept 
        : GameComponent(ComponentType{randomColour(), Constants::directionToSt(randomDirection())}) {}
    StripedBomb(const StripedBomb &) = default;
    StripedBomb(StripedBomb &&) = default;
private:
    /** @brief Returns a random direction (horizontal / verical) */
    Direction randomDirection() const {return static_cast<Direction>(rand() % 2);}
};

#endif
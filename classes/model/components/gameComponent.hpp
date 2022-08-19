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
#include "../../common/componentType.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
protected:
    ComponentType compType;
    const BlastType blastType;
    const Direction blastDirection;
public:
    GameComponent(ComponentType &&compType, BlastType blastType, Direction blastDirection) noexcept 
        : compType{std::move(compType)}, blastType{blastType}, blastDirection{blastDirection} {}
    GameComponent(ComponentType &&compType) noexcept
        : compType{std::move(compType)}, blastType{BlastType::SIMPLE}, blastDirection{Direction::NO_DIRECTION} {}
    virtual ~GameComponent() = default;

    virtual ComponentState pop() {return ComponentState::POPPED;}
    virtual Colour getColour() const {return compType.colour;}
    virtual BlastType getBlastType() const {return blastType;}
    virtual Direction getBlastDirection() const {return blastDirection;}
    virtual void explode() {}
    virtual ComponentType type() const {return compType;}
};

#endif
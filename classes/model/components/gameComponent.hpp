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
public:
    GameComponent(ComponentType &&compType, BlastType blastType) noexcept 
        : compType{std::move(compType)}, blastType{blastType} {}
    GameComponent(ComponentType &&compType) noexcept
        : compType{std::move(compType)}, blastType{BlastType::SIMPLE} {}
    virtual ~GameComponent() = default;

    virtual ComponentState pop() {return ComponentState::POPPED;}
    virtual Colour getColour() const {return compType.colour;}
    virtual BlastType getBlastType() const {return blastType;}
    virtual ComponentType type() const {return compType;}

protected:
    /** @brief Returns a random candy */
    Colour randomColour() const {return static_cast<Colour>(static_cast<Colour>(rand() % 6));}
};

#endif
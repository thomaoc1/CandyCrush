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
public:
    GameComponent(ComponentType &&compType) noexcept
        : compType{std::move(compType)} {}
    virtual ~GameComponent() = default;

    virtual ComponentState pop() {return ComponentState::POPPED;}
    virtual Colour getColour() const {return compType.colour;}
    virtual ComponentType type() const {return compType;}

protected:
    /** @brief Returns a random candy */
    Colour randomColour() const {return static_cast<Colour>(static_cast<Colour>(rand() % 6));}
};

#endif
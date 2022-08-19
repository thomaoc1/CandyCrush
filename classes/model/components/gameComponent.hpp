/**
 * @file gameComponent.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Base Class which generalises all GameComponents
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
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
    Colour randomColour() const {return static_cast<Colour>(static_cast<Colour>(rand() % 6));}
};

#endif
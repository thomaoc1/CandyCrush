#ifndef SPECIAL_BOMB_HPP
#define SPECIAL_BOMB_HPP

#include "gameComponent.hpp"

class SpecialBomb : public GameComponent {
    Component component;
public:
    SpecialBomb() 
        : GameComponent{ComponentType{Colour::DARK_RED, Component::SPECIAL_BOMB}, BlastType::SPECIAL, Direction::NO_DIRECTION} {}
    void setComponent(Component toPop) {component = toPop;}
    Component getComponent() const {return component;}
};

#endif
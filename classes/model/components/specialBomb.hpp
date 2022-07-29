#ifndef SPECIAL_BOMB_HPP
#define SPECIAL_BOMB_HPP

#include "gameComponent.hpp"

class SpecialBomb : public GameComponent {
    int component;
public:
    SpecialBomb() : GameComponent{Constants::ALL} {}
    void setComponent(int toPop) {component = toPop;}
    int getComponent() const {return component;}
    int type() const override {return Constants::SPECIAL_BOMB;}
};


#endif
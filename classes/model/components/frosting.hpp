#ifndef FROSTING_HPP
#define FROSTING_HPP

#include "gameComponent.hpp"

class Frosting : public GameComponent {
    int layers;
public:
    Frosting(int layers) noexcept 
        : GameComponent{ComponentType{Colour::CYAN, layers == 2 ? Component::FROSTING2 : Component::FROSTING1}}, layers{layers} {}
    
    ComponentState pop() override;
};

#endif
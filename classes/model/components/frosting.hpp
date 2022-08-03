#ifndef FROSTING_HPP
#define FROSTING_HPP

#include "gameComponent.hpp"

class Frosting : public GameComponent {
    int layers;
public:
    Frosting(int layers) noexcept 
        : GameComponent(layers == 2 ? Constants::FROSTING1 : Constants::FROSTING2), layers{layers} {}
    
    int pop() override;

    int type() const override {return layers == 1 ? Constants::FROSTING1 : Constants::FROSTING2 ;}
    std::string toString() const override {return "F" + std::to_string(layers);}
};

#endif
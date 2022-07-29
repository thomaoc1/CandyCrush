#ifndef FROSTING_HPP
#define FROSTING_HPP

#include "gameComponent.hpp"

class Frosting : public GameComponent {
    int layers = 2;

public:
    Frosting() noexcept : GameComponent(Constants::randomCandy(), 1, Constants::NO_DIRECTION) {}
    int type() const override {return layers==1 ? Constants::FROSTING1 : Constants::FROSTING2 ;}
    std::string toString() const override {return "F" + std::to_string(layers); }
    void explode() {--layers;}
};

#endif
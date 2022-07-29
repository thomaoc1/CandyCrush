#ifndef CHERRY_HPP
#define CHERRY_HPP

#include "gameComponent.hpp"

class Cherry : public GameComponent {
public:
    int type() const override {return Constants::CHERRY;}
    std::string toString() const override {return "C";}
};

#endif
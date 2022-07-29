#ifndef HAZELNUT_HPP
#define HAZELNUT_HPP

#include "gameComponent.hpp"

class Hazelnut : public GameComponent {
public:
    int type() const override {return Constants::CHERRY;}
    std::string toString() const override {return "C";}
};

#endif
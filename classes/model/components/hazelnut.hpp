#ifndef HAZELNUT_HPP
#define HAZELNUT_HPP

#include "gameComponent.hpp"

class Hazelnut : public GameComponent {
public:
    Hazelnut() : GameComponent{ComponentType{Colour::BROWN, Component::HAZELNUT}} {}
    Hazelnut(const Hazelnut &) = default;
    Hazelnut(Hazelnut &&) = default;
};

#endif
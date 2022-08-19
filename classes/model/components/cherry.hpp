#ifndef CHERRY_HPP
#define CHERRY_HPP

#include "gameComponent.hpp"

class Cherry : public GameComponent {
public:
    Cherry() : GameComponent{ComponentType{Colour::DARK_RED, Component::CHERRY}} {}
    Cherry(const Cherry &) = default;
    Cherry(Cherry &&) = default;
};

#endif
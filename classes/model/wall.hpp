#ifndef WALL_HPP
#define WALL_HPP

#include "gameComponent.hpp"

class Wall : public GameComponent {
public:
    std::string package() const override {return Constants::getWALL();};
};

#endif
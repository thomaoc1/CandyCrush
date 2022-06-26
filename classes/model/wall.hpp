#ifndef WALL_HPP
#define WALL_HPP

#include "cell.hpp"

class Wall : public Cell {
public:
    std::string package() const override {return Constants::getWALL();};
};

#endif
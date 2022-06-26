#ifndef CELL_HPP
#define CELL_HPP

#include "../constants/constants.hpp"

#include <string>

class Cell {
public:
    virtual ~Cell() {};
    virtual std::string package() const=0;
};

#endif
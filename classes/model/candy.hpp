#ifndef CANDY_HPP
#define CANDY_HPP

#include "cell.hpp"

class Candy : public Cell {
    std::string colour;
public:
    Candy() : Cell(), colour{Constants::randomCandy()} {}
    Candy(std::string colour) : Cell(), colour{colour} {}
    virtual ~Candy() {}
    virtual std::string package() const override {return colour;} 
};

#endif
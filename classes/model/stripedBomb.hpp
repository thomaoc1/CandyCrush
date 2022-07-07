#ifndef STRIPED_BOMB_HPP
#define STRIPED_BOMB_HPP

#include "candyBomb.hpp"

class StripedBomb : public CandyBomb {
public:
    StripedBomb(const std::string &colour) : CandyBomb(colour) {}
    StripedBomb() : CandyBomb(Constants::randomCandy()) {}
    std::string const package() const override {return Constants::STRIPED + CandyBomb::package();}
};

#endif
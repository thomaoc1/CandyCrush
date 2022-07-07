

#ifndef WRAPPED_BOMB_HPP
#define WRAPPED_BOMB_HPP

#include "candyBomb.hpp"

class WrappedBomb : public CandyBomb {
public:
    WrappedBomb(const std::string &colour) : CandyBomb(colour) {}
    WrappedBomb() : CandyBomb(Constants::randomCandy()) {}
    const std::string package() const override {return Constants::WRAPPED + CandyBomb::package();}
};

#endif
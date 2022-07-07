#ifndef WRAPPED_BOMB_HPP
#define WRAPPED_BOMB_HPP

#include "candy.hpp"

class WrappedBomb : public Candy {
public:
    WrappedBomb(int colour) : Candy(colour) {}
    WrappedBomb() : Candy(Constants::randomCandy()) {}
    int package() const override;
};

#endif
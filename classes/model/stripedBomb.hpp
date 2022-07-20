#ifndef STRIPED_BOMB_HPP
#define STRIPED_BOMB_HPP

#include "candy.hpp"

class StripedBomb : public Candy {
public:
    StripedBomb(int colour) : Candy(colour) {}
    StripedBomb() : Candy(Constants::randomCandy()) {}
    int type() const override;
};

#endif
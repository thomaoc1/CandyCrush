#ifndef SWAP_HPP
#define SWAP_HPP

#include "action.hpp"
#include "../../constants/constants.hpp"

class Swap : public Displacement {
public:
    Swap(const Point &start, const Point &dest) : Displacement(start, dest) {}
    int type() const override {return Constants::SWAP;}
};

#endif
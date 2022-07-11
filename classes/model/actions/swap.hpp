#ifndef SWAP_HPP
#define SWAP_HPP

#include "action.hpp"
#include "../../constants/constants.hpp"

class Swap : public Action {
public:
    int type() const override {return Constants::SWAP;}
};

#endif
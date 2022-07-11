#ifndef POP_HPP
#define POP_HPP

#include "action.hpp"
#include "../../constants/constants.hpp"

class Pop : public Action {
public:
    int type() const override {return Constants::POP;} 
};

#endif
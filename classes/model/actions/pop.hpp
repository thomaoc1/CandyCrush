#ifndef POP_HPP
#define POP_HPP

#include "suppression.hpp"
#include "../../constants/constants.hpp"

class Pop : public Suppression {
public:
    Pop(const std::vector<Point> &victims) : Suppression(victims) {}
    int type() const override {return Constants::POP;} 
};

#endif
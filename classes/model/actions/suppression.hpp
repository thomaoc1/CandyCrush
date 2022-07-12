#ifndef SUPPRESSION_HPP
#define SUPPRESSION_HPP

#include "action.hpp"

#include <vector>

class Suppression : public Action {
public:
    Suppression(const Point &target) : Action(target, target) {}
    int type() const override {return Constants::SUPPRESSION;}
};
#endif
#ifndef DISPLACEMENT_HPP
#define DISPLACEMENT_HPP

#include "action.hpp"

#include <vector>

class Displacement : public Action {
public:
    Displacement(const Point &start, const Point &dest) : Action(start, dest) {}
    int type() const {return Constants::DISPLACEMENT;}
};
#endif
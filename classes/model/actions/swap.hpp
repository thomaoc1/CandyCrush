#ifndef SWAP_HPP
#define SWAP_HPP

#include "action.hpp"
#include "../../constants/constants.hpp"

class Swap : public Displacement {
    typedef std::pair< Point, Point > PointPair; 
public:
    Swap(const Point &c1, const Point &c2) : Displacement(std::vector<PointPair>{{c1, c2}}) {}
    int type() const override {return Constants::SWAP;}
};

#endif
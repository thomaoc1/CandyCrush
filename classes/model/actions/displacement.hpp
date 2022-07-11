#ifndef DISPLACEMENT_HPP
#define DISPLACEMENT_HPP

#include "action.hpp"

#include <vector>

class Displacement : public Action {
    typedef std::pair< Point, Point > PointPair; 
    PointPair couple;
public:
    Displacement(PointPair couple) : couple{couple} {}
    virtual ~Displacement() {};
    virtual Point getFirst() const {return couple.first;}
    virtual Point getSecond() const {return couple.second;}
};
#endif
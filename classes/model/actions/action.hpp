#ifndef ACTION_HPP
#define ACTION_HPP

#include "../point.hpp"

class Action {
    Point start;
    Point dest;
public:
    Action(const Point &start, const Point &dest) : start{start}, dest{dest} {};
    virtual ~Action() {}
    virtual Point getStart() const {return start;}
    virtual Point getDest() const {return dest;}
    virtual int type() const=0;
};

#endif
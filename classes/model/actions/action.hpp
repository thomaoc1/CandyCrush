#ifndef ACTION_HPP
#define ACTION_HPP

#include "../point.hpp"

class Action {
public:
    Action() {};
    virtual ~Action() {}
    virtual int type() const=0;
};

#endif
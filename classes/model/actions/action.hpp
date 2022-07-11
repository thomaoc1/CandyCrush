#ifndef ACTION_HPP
#define ACTION_HPP

#include "../point.hpp"

#include <vector>

class Action {
    typedef std::pair< Point, Point > PointPair; 
    std::vector<PointPair> victims;
public:
    Action() {};
    virtual ~Action() {}
    virtual void setVictims(const std::vector<PointPair> &vict) {victims = vict;}
    virtual int victimeCount() const {return victims.size();}
    virtual PointPair getVictims(int i) const {return victims[i];}
    virtual int type() const=0;
};

#endif
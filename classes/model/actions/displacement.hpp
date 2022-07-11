#ifndef DISPLACEMENT_HPP
#define DISPLACEMENT_HPP

#include "action.hpp"

#include <vector>

class Displacement : public Action {
    typedef std::pair< Point, Point > PointPair; 
    std::vector<PointPair> victims;
public:
    Displacement(const std::vector<PointPair> &victims) : victims{victims} {}
    virtual ~Displacement() {};
    virtual void setVictims(const std::vector<PointPair> &vict) {victims = vict;}
    virtual int victimeCount() const {return static_cast<int>(victims.size());}
    virtual PointPair getVictims(int i) const {return victims[i];}
};
#endif
#ifndef SUPPRESSION_HPP
#define SUPPRESSION_HPP

#include "action.hpp"

#include <vector>

class Suppression : public Action {
    std::vector< Point > victims;
public:
    Suppression(const std::vector<Point> &victims) : victims{victims} {}
    virtual ~Suppression() {};
    virtual void setVictims(const std::vector<Point> &vict) {victims = vict;}
    virtual void addVictim(Point vict) {victims.push_back(vict);}
    virtual int victimeCount() const {return static_cast<int>(victims.size());}
    virtual Point getVictims(int i) const {return victims[i];}
};
#endif
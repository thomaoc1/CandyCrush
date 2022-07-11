#ifndef DROP_HPP
#define DROP_HPP

#include "displacement.hpp"
#include "../../constants/constants.hpp"

class Drop : public Displacement {
public:
    Drop(const Point &c1, const Point &c2) : Displacement{{c1, c2}} {}
    int type() const override {return Constants::DROP;} 
};

#endif
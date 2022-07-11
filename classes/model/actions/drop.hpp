#ifndef DROP_HPP
#define DROP_HPP

#include "displacement.hpp"
#include "../../constants/constants.hpp"

class Drop : public Displacement {
public:
    int type() const override {return Constants::DROP;} 
};

#endif
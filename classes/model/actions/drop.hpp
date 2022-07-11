#ifndef DROP_HPP
#define DROP_HPP

#include "action.hpp"
#include "../../constants/constants.hpp"

class Drop : public Action {
public:
    int type() const override {return Constants::DROP;} 
};

#endif
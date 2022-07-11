#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../constants/constants.hpp"

class ComponentDisplay {
public:
    ComponentDisplay() {}
    virtual ~ComponentDisplay() {}
    virtual void draw(int, int) const=0;
};

#endif
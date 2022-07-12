#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../constants/constants.hpp"
#include "../model/point.hpp"

class ComponentDisplay {
    Point center;
public:
    ComponentDisplay(Point center) : center{center} {}
    virtual Point getCenter() const {return center;}
    virtual ~ComponentDisplay() {}
    virtual void draw() const=0;
};

#endif
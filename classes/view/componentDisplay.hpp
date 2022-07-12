#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../constants/constants.hpp"
#include "../model/point.hpp"

class ComponentDisplay {
    Point center;
public:
    ComponentDisplay(Point center) : center{center} {}
    virtual ~ComponentDisplay() {}
    virtual Point getCenter() const {return center;}
    virtual void setCenter(const Point &dest) {center = dest;}
    virtual void draw()=0;
};

#endif
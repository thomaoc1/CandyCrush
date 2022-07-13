#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

class Animation;

#include "../constants/constants.hpp"
#include "../model/point.hpp"
#include "animation/animation.hpp"
#include "animation/moveAnimation.hpp"

#include <memory>
#include <queue>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class ComponentDisplay {
    Point center;
protected:
    Fl_Color fl_colour;
    std::shared_ptr<Animation> animation;
    std::queue< std::shared_ptr<Animation> > animations;
public:
    ComponentDisplay(const Point &center) : center{center}, fl_colour{FL_BLACK} {}
    ComponentDisplay(Point center, int colour);
    virtual ~ComponentDisplay() {}

    virtual Point getCenter() const {return center;}
    virtual bool inAnimation() const;
    virtual void setCenter(const Point &dest) {center = dest;}

    virtual void moveAnimate(const Point &dest);
    virtual void removeAnimate();
    virtual void swapAnimate(ComponentDisplay * other);

    virtual void draw();
    virtual void drawShape() const=0;
};

#endif
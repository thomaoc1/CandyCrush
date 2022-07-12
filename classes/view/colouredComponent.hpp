#ifndef COLOURED_COMPONENT_HPP
#define COLOURED_COMPONENT_HPP

class ColouredComponent;

#include "componentDisplay.hpp"
#include "animation.hpp"
#include "moveAnimation.hpp"

#include <memory>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class ColouredComponent : public ComponentDisplay {
protected:
    Fl_Color fl_colour;
    std::shared_ptr<Animation> animation{nullptr};
public:
    ColouredComponent(Point center, int colour);
    virtual Fl_Color getFLColour() const {return fl_colour;} 
    virtual void drawShape() const=0;
    virtual void moveAnimate(const Point &dest);
    virtual void swapAnimate(ColouredComponent * /*other*/) {};
    virtual void popAnimate() {};
};

#endif
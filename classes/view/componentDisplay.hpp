#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../constants/constants.hpp"
#include "../model/point.hpp"

#include <memory>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class Animation;

class ComponentDisplay {
    Point center;
protected:
    Fl_Color fl_colour;
    std::shared_ptr<Animation> animation;
    int size;
public:
    ComponentDisplay(const Point &center, int size) : center{center}, fl_colour{FL_BLACK}, size{size} {}
    ComponentDisplay(Point center, int size, int colour);
    virtual ~ComponentDisplay() {}

    virtual Point getCenter() const {return center;}
    virtual Fl_Color getColor() const {return fl_colour;}
    virtual int getSize() const {return size;}
    virtual bool inAnimation() const;

    virtual void setCenter(const Point &dest) {center = dest;}
    virtual void setSize(int newSize) {size = newSize;}

    virtual void fillAnimate();
    virtual void moveAnimate(const Point &dest);
    virtual void popAnimate();
    virtual void swapAnimate(std::shared_ptr<ComponentDisplay> other);

    virtual void draw();
    virtual void drawShape() const=0;
};

#endif
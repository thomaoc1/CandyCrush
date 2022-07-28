/**
 * File : 
 *  componentDisplay.hpp
 *
 * Decription :
 *  Abstract class which generalises the visual representation of gameComponents.
 * 
 * Dependencies:
 *  constants.hpp
 *  point.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../../constants/constants.hpp"
#include "../../shared/point.hpp"
#include "../shapes/shape.hpp"

#include <memory>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class Animation;

class ComponentDisplay {
protected:
    Point center;
    Fl_Color fl_colour;
    int size;

    std::shared_ptr<Animation> animation;
    std::shared_ptr<Shape> shape;
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
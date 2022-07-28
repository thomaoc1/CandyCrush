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
    std::shared_ptr<Animation> animation;
    std::shared_ptr<Shape> shape;
public:
    ComponentDisplay(std::shared_ptr<Shape> shape) noexcept : shape{shape} {};
    ComponentDisplay(const ComponentDisplay &other) = default;
    ComponentDisplay(ComponentDisplay &&other) = default;
    virtual ~ComponentDisplay() = default;

    virtual Point getCenter() const {return shape->getCenter();}
    virtual int getSize() const {return shape->getSize();}
    virtual bool inAnimation() const;

    virtual void setCenter(const Point &dest) {shape->setCenter(dest);}
    virtual void setSize(int newSize) {shape->setSize(newSize);}

    virtual void fillAnimate();
    virtual void moveAnimate(const Point &dest);
    virtual void popAnimate();
    virtual void swapAnimate(std::shared_ptr<ComponentDisplay> other);

    virtual void draw();
    virtual void drawShape() const;
};

#endif
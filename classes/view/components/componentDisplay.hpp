/**
 * @file componentDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which generalises the graphical representation of
 *  all game components.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef COMPONENT_DISPLAY_HPP
#define COMPONENT_DISPLAY_HPP

#include "../../common/constants.hpp"
#include "../../common/point.hpp"
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
    bool popping = false;
public:
    ComponentDisplay(std::shared_ptr<Shape> shape) noexcept : shape{shape} {};
    ComponentDisplay(const ComponentDisplay &other) = default;
    ComponentDisplay(ComponentDisplay &&other) = default;
    virtual ~ComponentDisplay() = default;

    virtual Point getCenter() const {return shape->getCenter();}
    virtual double getSize() const {return shape->getSize();}

    virtual bool inAnimation() const;

    virtual void setCenter(const Point &dest) {shape->setCenter(dest);}
    virtual void setSize(double newSize) {shape->setSize(newSize);}

    virtual void fillAnimate();
    virtual void moveAnimate(const Point &dest);
    virtual void popAnimate();
    virtual void swapAnimate(std::shared_ptr<ComponentDisplay> other);
    virtual void suggAnimate();

    virtual void draw();
    virtual void drawShape() const;

    virtual AnimPriority animationType() const; 
};

#endif
/**
 * File : 
 *  shape.hpp
 *
 * Decription :
 *  Abstract class which generalises the representation of shapes.
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */
#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../../constants/constants.hpp"
#include "../../shared/point.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class Shape {
protected:
    Point center;
    Fl_Color colour;
    double size;
public:
    Shape(const Point &center, int colours, double size) noexcept 
        : center{center}, colour{Constants::associatedFLColour(colours)}, size{size} {};

    Shape(const Point &center, Fl_Color colours, double size) noexcept 
        : center{center}, colour{colours}, size{size} {};

    Shape(const Shape &) = default;
    Shape(Shape &&) = default;

    virtual Point getCenter() const {return center;}
    virtual double getSize() const {return size;}

    virtual void setSize(double newSize) {size = newSize;} 
    virtual void setCenter(const Point &dest) {center = dest;}

    virtual void draw() const=0;
};

#endif
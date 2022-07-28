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
public:
    Shape(const Point &center, Fl_Color colour) noexcept : center{center}, colour{colour} {};
    Shape(const Shape &) = default;
    Shape(Shape &&) = default;

    virtual void draw() const=0;
};

#endif
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
    const double radius;
public:
    Circle(const Point &center, Fl_Color colour, double radius) : Shape{center, colour}, radius{radius} {}
    Circle(const Circle &) = default;
    Circle(Circle &&) = default;

    void draw() const override;
};

#endif
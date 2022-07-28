#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
public:
    Circle(const Point &center, int colour, int radius) : Shape{center, colour, radius} {}
    Circle(const Circle &) = default;
    Circle(Circle &&) = default;

    void draw() const override;
};

#endif
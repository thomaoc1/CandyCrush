/**
 * @file circle.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation
 *  of a Circle shape.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
public:
    Circle(const Point &center, Colour colour, double radius) : Shape{center, colour, radius} {}
    Circle(const Circle &) = default;
    Circle(Circle &&) = default;

    void draw() const override;
};

#endif
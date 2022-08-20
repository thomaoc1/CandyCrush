/**
 * @file cherryShape.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation
 *  of a Cherry shape.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */


#ifndef CHERRYSHAPE_HPP
#define CHERRYSHAPE_HPP

#include "shape.hpp"

class CherryShape : public Shape {
public:
    CherryShape(const Point &center, double radius) : Shape{center, Colour::DARK_RED, radius} {}
    CherryShape(const CherryShape &) = default;
    CherryShape(CherryShape &&) = default;

    void draw() const override;
};

#endif
#ifndef CHERRYSHAPE_HPP
#define CHERRYSHAPE_HPP

#include "shape.hpp"

class CherryShape : public Shape {
public:
    CherryShape(const Point &center, int radius) : Shape{center, Constants::CHERRY, radius} {}
    CherryShape(const CherryShape &) = default;
    CherryShape(CherryShape &&) = default;

    void draw() const override;
};

#endif
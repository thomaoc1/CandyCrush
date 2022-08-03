#ifndef HAZELSHAPE_HPP
#define HAZELSHAPE_HPP

#include "shape.hpp"

class HazelShape : public Shape {
public:
    HazelShape(const Point &center, double radius) : Shape{center, Constants::HAZELNUT, radius} {}
    HazelShape(const HazelShape &) = default;
    HazelShape(HazelShape &&) = default;

    void draw() const override;
};

#endif
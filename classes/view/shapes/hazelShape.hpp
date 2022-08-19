/**
 * @file hazelShape.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation
 *  of a Hazelnut shape.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef HAZELSHAPE_HPP
#define HAZELSHAPE_HPP

#include "shape.hpp"

class HazelShape : public Shape {
public:
    HazelShape(const Point &center, double radius) : Shape{center, Colour::BROWN, radius} {}
    HazelShape(const HazelShape &) = default;
    HazelShape(HazelShape &&) = default;

    void draw() const override;
};

#endif
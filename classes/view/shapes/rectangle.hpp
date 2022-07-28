#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
    Fl_Boxtype type;
public:
    Rectangle(const Point &center, int fillColour, int size, Fl_Boxtype type) 
                : Shape{center, fillColour, size}, type{type} {}
                                                                                          
    Rectangle(const Rectangle &) = default;
    Rectangle(Rectangle &&) = default;

    void draw() const;
};


#endif
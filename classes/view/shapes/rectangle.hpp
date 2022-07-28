#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
    Fl_Color frameColour;
    const int size;
public:
    Rectangle(const Point &center, Fl_Color fillColour, Fl_Color frameColour, int size) : Shape{center, colour}, 
                                                                                          frameColour{frameColour}, 
                                                                                          size{size} {}
    Rectangle(const Rectangle &) = default;
    Rectangle(Rectangle &&) = default;

    void draw() const;
};


#endif
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
    int w, h;
    Fl_Boxtype type;
public:
    Rectangle(const Point &center, int fillColour, int size, Fl_Boxtype type) 
                : Shape{center, fillColour, size}, w{size}, h{size}, type{type} {}
    Rectangle(const Point &center, int fillColour, int w, int h, Fl_Boxtype type) 
                : Shape{center, fillColour, w}, w{w}, h{h}, type{type} {}
                                                                                          
    Rectangle(const Rectangle &) = default;
    Rectangle(Rectangle &&) = default;

    void draw() const;
};


#endif
/**
 * @file rectangle.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation
 *  of a Rectangle shape.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
    double w, h;
    Fl_Boxtype type;
public:
    Rectangle(const Point &center, Colour fillColour, double size, Fl_Boxtype type) 
                : Shape{center, fillColour, size}, w{size}, h{size}, type{type} {}
                
    Rectangle(const Point &center, Colour fillColour, double w, double h, Fl_Boxtype type) 
                : Shape{center, fillColour, w}, w{w}, h{h}, type{type} {}

    Rectangle(const Point &center, Fl_Color fillColour, double w, double h, Fl_Boxtype type) 
                : Shape{center, fillColour, w}, w{w}, h{h}, type{type} {}
    
    Rectangle(const Point &center, Fl_Color fillColour, double size, Fl_Boxtype type) 
                : Shape{center, fillColour, size}, w{size}, h{size}, type{type} {}

                                        
    Rectangle(const Rectangle &) = default;
    Rectangle(Rectangle &&) = default;

    void setSize(double newSize) override {w = newSize; h = newSize;}
    double getWidth() const {return w;}
    double getHeight() const {return h;}
    double getSize() const override {return w;}

    void draw() const;
};


#endif
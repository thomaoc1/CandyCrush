#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP


#include "../shapes/rectangle.hpp"


class Background {
    Rectangle rectangle;
public:
    Background(Fl_Color colour)
        : rectangle{{static_cast<int>(Constants::WINDOW_WIDTH / 2), static_cast<int>(Constants::WINDOW_HEIGHT / 2)}, 
                        colour, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, FL_FLAT_BOX} {}
    Background(const Background &) = default;
    Background(Background &&) = default;

    Point getCenter() const {return rectangle.getCenter();}

    void draw() const {rectangle.draw();} 
};


#endif
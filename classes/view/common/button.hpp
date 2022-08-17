#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../shapes/rectangle.hpp"
#include "../text/text.hpp"

class Button {
    Rectangle r;
    Text text;
    bool clicked = false;
public:
    Button(const Point &center, const std::string &text, Fl_Color fillColour, double w, double h)
        : r{center, fillColour, w, h, FL_BORDER_FRAME}, 
            text{Point{center.x, static_cast<int>(center.y - h / 2)}, text, FL_HELVETICA, 25} {}
    Button(const Button &) = default;
    Button(Button &&) = default;

    void draw() const;
    bool isClicked(const Point &mouseLoc) const {return inButton(mouseLoc);}

private:
    bool inButton(const Point &mouseLoc) const;
};


#endif
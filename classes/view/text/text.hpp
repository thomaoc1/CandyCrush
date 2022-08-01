#ifndef TEXT_HPP
#define TEXT_HPP

#include "../../shared/point.hpp"

#include <string>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class Text {
protected:
    Point center;
    std::string text;
    Fl_Font font;
    int size;
public:
    Text(const Point &center, const std::string &text, Fl_Font font, int size)
        : center{center}, text{text}, font{font}, size{size} {}
    Text() = default;
    Text(const Text &) = default;
    Text(Text &&) = default;
    
    virtual std::string getText() const {return text;}

    virtual void clear() {text = "";}
    virtual void setText(const std::string &newText) {text = newText;}
    virtual void setText(std::string &&newText) {text = std::move(newText);}
    virtual void setSize(int newSize) {size = newSize;}
    virtual void setCenter(const Point &dest) {center = dest;}
    virtual void setCenter(Point &&dest) {center = std::move(dest);}
    virtual void draw() const=0;
};

#endif
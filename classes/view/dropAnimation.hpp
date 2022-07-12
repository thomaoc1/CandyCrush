#ifndef DROP_ANIMATION_HPP
#define DROP_ANIMATION_HPP

class DropAnimation;

#include "../model/point.hpp"
#include "cellDisplay.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>


struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() {
    fl_pop_matrix();
  }
};


class DropAnimation {
    const int animationTime = 60;
    int time = 0;
    CellDisplay * cell;
public:
    DropAnimation(CellDisplay * cell) : cell{cell} {}
    void draw(const Point &dest);
    bool animationOver() const {return time < animationTime;}
private:
    Point currentTranslation(const Point &dest);
};

#endif
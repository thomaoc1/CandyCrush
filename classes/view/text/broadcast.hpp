#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#include "textDisplay.hpp"
#include "../shapes/rectangle.hpp"

class BroadcastBox {
    Rectangle box;
    TextDisplay text;
public:
    BroadcastBox(const std::string &s = "")
     : box{Point{static_cast<int>(Constants::GAME_WINDOW_Xi + Constants::CELL_SIZE / 2), 75}, 
            Constants::WALL, static_cast<int>(Constants::GAME_WINDOW_Xf - Constants::GAME_WINDOW_Xi), 150, FL_BORDER_FRAME}, 
        text{Point{285, 100}, s, FL_HELVETICA, 30} {}

    void clear() {text.clear();}
    void setMessage(const std::string &s) {text.setText(s);}
    void setMessage(std::string &&s) {text.setText(s);}

    void draw() const {text.draw(); box.draw();}
};


#endif
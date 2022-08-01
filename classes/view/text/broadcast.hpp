#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#include "textDisplay.hpp"
#include "../shapes/rectangle.hpp"

class BroadcastBox {
    Rectangle box;
    TextDisplay text;
public:
    BroadcastBox(const std::string &s = "")
     : box{Point{static_cast<int>((Constants::GAME_WINDOW_Xi + Constants::GAME_WINDOW_Xf) / 2), 125}, 
            Constants::WALL, static_cast<int>(Constants::GAME_WINDOW_Xf - Constants::GAME_WINDOW_Xi), 150, FL_BORDER_FRAME}, 
        text{box.getCenter(), s, FL_HELVETICA, 30} {std::cout << box.getCenter() << std::endl; }

    void clear() {text.clear();}
    void setMessage(const std::string &s) {text.setText(s);}
    void setMessage(std::string &&s) {text.setText(s);}

    void draw() const {text.draw(); box.draw();}
};


#endif
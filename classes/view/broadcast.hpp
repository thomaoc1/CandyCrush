#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#include "text/textDisplay.hpp"

class Broadcast {
    TextDisplay text;
public:
    Broadcast() = default;
    Broadcast(const std::string &s) : text{{200, 200}, s, FL_HELVETICA, 10} {}

    void setMessage(const std::string &s);
    void setMessage(std::string &&s);

    void draw() const {text.draw();}
};


#endif
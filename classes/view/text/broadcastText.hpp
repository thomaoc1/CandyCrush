#ifndef BROADCAST_TEXT_HPP
#define BROADCAST_TEXT_HPP

#include "text.hpp"

class BroadcastText : public Text {
public:
    BroadcastText (const Point &boxCenter, int size, const std::string text="") 
        : Text{boxCenter, text, FL_HELVETICA, size} {}
    BroadcastText() = default;
    BroadcastText(const BroadcastText &) = default;
    BroadcastText(BroadcastText &&) = default;

    void draw() const override;
};

#endif
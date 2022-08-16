#ifndef TITLE_SCREEN_HPP 
#define TITLE_SCREEN_HPP

#include "../common/background.hpp"
#include "../text/text.hpp"

class TitleScreen {
    Background bg;
    Text names;
public:
    TitleScreen() : bg{FL_WHITE}, names{bg.getCenter(), "Thomas & Marcus", FL_HELVETICA, 25} {}
    TitleScreen(const TitleScreen &) = default;
    TitleScreen(TitleScreen &&) = default;

    void draw() const {bg.draw(); names.draw();}
};

#endif
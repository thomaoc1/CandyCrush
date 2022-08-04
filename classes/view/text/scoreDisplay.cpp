#include "scoreDisplay.hpp"


void ScoreDisplay::draw() const {
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, size);
    std::cout<<"size : "<< size << std::endl;
    int width = 0 , height = 0;
    // Sometimes 50,36 sometimes 102,18
    fl_measure(text.c_str(), width, height, false);


    std::cout<<"w,h :"<<width<<" "<<height<<std::endl;
    std::cout<<"center "<<center.x<<" "<<center.y<<std::endl;

    fl_draw(text.c_str(), center.x - width / 2, center.y + ( 2 * height ));
}   
